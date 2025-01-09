#include "core/object/class_db.h"
#include "core/os/keyboard.h"
#include "core/string/string_name.h"
#include "core/string/ustring.h"
#include "core/templates/vector.h"
#include "core/variant/callable.h"
#include "core/variant/typed_array.h" // DOC: Is used in retval of PG_Str::to_arr_of_str().
#include "core/variant/variant.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/exts/pg_arr.h"
#include "modules/pg_g1/exts/pg_str.h"
#include "modules/pg_g1/exts/pg_vec.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


// TODO: Prefer to put these in classes corresponding to the template type,
// e.g. pg_sn.cpp for PG_Vec::last<StringName>(). Look up "extern template".
// It's better to include just PG_Vec in each of those files, rather than include them ALL in PG_Vec.
template bool PG_Vec::idx_ok(const Vector<Node3D *> &v, int i);

// DOC: As example. Remove later if not needed.
template Node3D *PG_Vec::get_by_idx<Node3D *>(const Vector<Node3D *> &a, int idx, Node3D *&def);

template StringName PG_Vec::last<StringName>(Vector<StringName> &v);

template StringName PG_Vec::pop_back<StringName>(Vector<StringName> &v);

template int PG_Vec::rm_adj_dupes<String>(Vector<String> &v);

template int PG_Vec::resize_until_item<StringName>(Vector<StringName> &v, const StringName &item, bool pop_found_item);

template Vector<StringName> PG_Vec::from_typed_arr(TypedArray<StringName> a);


//////////////////////////////////////////////////
//////////////////////////////////////////////////


template <typename T>
bool PG_Vec::idx_ok(const Vector<T> &v, int idx) {
	return idx >= 0 && idx < v.size();
}


//////////////////////////////////////////////////


template <typename T>
T PG_Vec::get_by_idx(const Vector<T> &v, int idx, T &def) {
	return PG_Vec::idx_ok(v, idx) ? v[idx] : def;
}


template <typename T>
T PG_Vec::get_by_idx_wrap(const Vector<T> &v, int idx, T &def) {
	return !v.is_empty() ? v[idx % v.size()] : def;
}


//////////////////////////////////////////////////


template <typename T>
T PG_Vec::first_f(const Vector<T> &v, const Callable &f, T &def) {
	for (const T &e : v) {
		if (f.call(e)) {
			return e;
		}
	}
	return def;
}


//////////////////////////////////////////////////


template <typename T>
T PG_Vec::last(Vector<T> &v) {
	if (v.is_empty()) {
		return T();
	}
	return v.get(v.size() - 1);
}


template <class T>
T PG_Vec::last(const Vector<T> &v, T &def) {
	return !v.is_empty() ? v[-1] : def;
}


template <class T>
T PG_Vec::penultimate(const Vector<T> &v, T &def) {
	return v.size() > 1 ? v[-2] : def;
}


//////////////////////////////////////////////////


template <typename T>
T PG_Vec::pop_back(Vector<T> &v) {
	T e = v.get(v.size() - 1);
	v.remove_at(v.size() - 1);
	return e;
}


//////////////////////////////////////////////////


template <typename T>
int PG_Vec::rm_adj_dupes(Vector<T> &v) {
	int r = 0;
	for (int i = 1; i < v.size(); i++) {
		if (v[i] == v[i - 1]) {
			v.remove_at(i);
			i--;
			r++;
		}
	}
	return r;
}


//////////////////////////////////////////////////


template <typename T>
int PG_Vec::resize_until_item(Vector<T> &v, const T &item, bool pop_found_item) {
	int i = v.rfind(item);
	if (i > -1) {
		v.resize(i + !pop_found_item);
	}
	return v.size();
}


//////////////////////////////////////////////////


template <typename T>
Vector<T> PG_Vec::from_typed_arr(TypedArray<T> a) {
	Vector<T> r;
	for (T e : a) {
		r.append(e);
	}
	return r;
}


//////////////////////////////////////////////////


Vector<Key> PG_Vec::to_arr_of_valid_keycodes(const Variant &v) {
	Vector<Key> r;
	if (!PG_Str::is_str_arr(v)) {
		return r;
	}
	for (const String &s : PG_Str::to_str_arr(v)) {
		Key k = find_keycode(s);
		if (k != Key::NONE) {
			r.append(k);
		}
	}
	return r;
}


//////////////////////////////////////////////////


template <typename T>
Vector<T> PG_Vec::get_interleaved(const Vector<T> &v, const T &item, bool also_if_empty) {
	Vector<T> r;
	if (v.is_empty()) {
		if (also_if_empty) {
			r.append(item);
		}
		return r;
	}
	r.resize(2 * v.size() - 1);
	r.fill(item);
	for (int i : r.size()) {
		if (i % 2 == 0) {
			r[i] = v[i / 2];
		}
	}
	return r;
}


//////////////////////////////////////////////////


void PG_Vec::_bind_methods() {
#ifdef PG_GD_FNS
#endif
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
