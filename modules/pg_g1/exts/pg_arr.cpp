#include "core/math/math_funcs.h"
#include "core/object/class_db.h"
#include "core/os/keyboard.h"
#include "core/templates/pair.h"
#include "core/variant/callable.h"
#include "core/variant/variant.h"
#include "core/variant/variant_utility.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/exts/pg_arr.h"
#include "modules/pg_g1/exts/pg_str.h"
#include "modules/pg_g1/types/pg_typedefs.h"
#include "scene/3d/node_3d.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


bool PG_Arr::is_arr(const Vrt &v) {
	return v.get_type() == Vrt::ARRAY;
}


bool PG_Arr::is_arr_of_str(const Vrt &v) {
	if (!is_arr(v)) {
		return false;
	}
	for (Vrt e : to_arr(v)) {
		if (!PG_Str::is_str(e)) {
			return false;
		}
	}
	return true;
}


//////////////////////////////////////////////////


Arr PG_Arr::to_arr(const Vrt &v) {
	return VUF::type_convert(v, Vrt::ARRAY);
}


TA<int> PG_Arr::to_arr_of_int(const Arr &a) {
	return assign<int>(a);
}


TA<V2> PG_Arr::to_arr_of_v2(const Arr &a) {
	return assign<V2>(a);
}


TA<V3> PG_Arr::to_arr_of_v3(const Arr &a) {
	return assign<V3>(a);
}


TA<Str> PG_Arr::to_arr_of_str(const Arr &a) {
	return assign<Str>(a);
}


TA<Node3D> PG_Arr::to_arr_of_node_3d(const Arr &a) {
	return assign<Node3D>(a);
}


Vec<Key> PG_Arr::to_arr_of_valid_keycodes(const Vrt &v) {
	Vec<Key> r;
	if (!is_arr_of_str(v)) {
		return r;
	}
	for (const Str &e : to_arr_of_str(v)) {
		Key k = find_keycode(e);
		if (k != Key::NONE) {
			r.append(k);
		}
	}
	return r;
}


Arr PG_Arr::from_pair(const Pair<Vrt, Vrt> &v) {
	Arr r;
	r.append(v.first);
	r.append(v.second);
	return r;
}


//////////////////////////////////////////////////


TA<Str> PG_Arr::mk_ta_str(Str s1, Str s2, Str s3, Str s4) {
	TA<Str> a;
	if (s1 != "") {
		a.append(s1);
	}
	if (s2 != "") {
		a.append(s2);
	}
	if (s3 != "") {
		a.append(s3);
	}
	if (s4 != "") {
		a.append(s4);
	}
	return a;
}


SNV PG_Arr::mk_snv(SN s1, SN s2, SN s3, SN s4) {
	SNV v;
	if (s1) {
		v.append(s1);
	}
	if (s2) {
		v.append(s2);
	}
	if (s3) {
		v.append(s3);
	}
	if (s4) {
		v.append(s4);
	}
	return v;
}


//////////////////////////////////////////////////


bool PG_Arr::idx_ok(const Arr &a, int i) {
	return i >= 0 && i < a.size();
}

template <typename T>
bool PG_Arr::idx_ok(const Vec<T> &v, int i) {
	return i >= 0 && i < v.size();
}
template bool PG_Arr::idx_ok(const Vec<Node3D *> &v, int i);


template <typename T>
T PG_Arr::get_by_idx(const Vec<T> &v, int idx, T &def) {
	return PG_Arr::idx_ok(v, idx) ? v[idx] : def;
}
template Node3D *PG_Arr::get_by_idx<Node3D *>(const Vec<Node3D *> &a, int idx, Node3D *&def); // DOC: As example. Remove later if not needed.

#ifdef PG_GD_FNS
Vrt PG_Arr::_gd_get_by_idx(const Arr &a, int idx, const Vrt &def) {
	return PG_Arr::idx_ok(a, idx) ? a[idx] : def;
}
#endif


template <typename T>
T PG_Arr::get_by_idx_wrap(const Vec<T> &v, int idx, T &def) {
	return !v.is_empty() ? v[idx % v.size()] : def;
}

#ifdef PG_GD_FNS
Vrt PG_Arr::_gd_get_by_idx_wrap(const Arr &a, int idx, const Vrt &def) {
	return !a.is_empty() ? a[idx % a.size()] : def;
}
#endif


template <class T>
T PG_Arr::last(const Vec<T> &v, T &def) {
	return !v.is_empty() ? v[-1] : def;
}

#ifdef PG_GD_FNS
Vrt PG_Arr::_gd_last(const Arr &a, const Vrt &def) {
	return !a.is_empty() ? a[-1] : def;
}
#endif


template <class T>
T PG_Arr::penultimate(const Arr &v, T &def) {
	return v.size() > 1 ? v[-2] : def;
}

#ifdef PG_GD_FNS
Vrt PG_Arr::_gd_penultimate(const Arr &a, const Vrt &def) {
	return a.size() > 1 ? a[-2] : def;
}
#endif


TA<int> PG_Arr::find_idxs(const Arr &a, const Vrt &v) {
	TA<int> r = TA<int>();
	for (int i = 0; i < a.size(); i++) {
		if (a[i] == v) {
			r.append(i);
		}
	}
	return r;
}


bool PG_Arr::has_any_in_common(const Arr &a1, const Arr &a2) {
	for (const Vrt &e : a1) {
		if (a2.has(e)) {
			return true;
		}
	}
	return false;
}


int PG_Arr::get_approx_v_idx(const Arr &a, const Vrt &v) {
	for (int i = 0; i < a.size(); i++) {
		if (Math::is_equal_approx(double(a[i]), double(v))) {
			return i;
		}
	}
	return -1;
}


//////////////////////////////////////////////////


bool PG_Arr::set_last(Arr &a, const Vrt &v, bool add_if_empty) {
	if (a.is_empty()) {
		if (add_if_empty) {
			a.append(v);
			return true;
		}
		return false;
	}
	a[a.size() - 1] = v;
	return true;
}


bool PG_Arr::append_if_diff_from_last(Arr &a, const Vrt &v) {
	if (a.back() != v) {
		a.append(v);
		return true;
	}
	return false;
}


//////////////////////////////////////////////////


template <typename T>
T PG_Arr::first_f(const Vec<T> &v, const Callable &f, T &def) {
	for (const T &e : v) {
		if (f.call(e)) {
			return e;
		}
	}
	return def;
}

#ifdef PG_GD_FNS
Vrt PG_Arr::_gd_first_f(const Arr &a, const Callable &f, const Vrt &def) {
	for (const Vrt &e : a) {
		if (f.call(e)) {
			return e;
		}
	}
	return def;
}
#endif


//////////////////////////////////////////////////


int PG_Arr::rm_all_v(Arr &a, const Vrt &v) {
	int r = 0;
	for (int i = 0; i < a.size(); i++) {
		if (a[i] == v) {
			a.remove_at(i);
			i--;
			r++;
		}
	}
	return r;
}


int PG_Arr::rm_adj_dupes(Arr &a) {
	int r = 0;
	for (int i = 1; i < a.size(); i++) {
		if (a[i] == a[i - 1]) {
			a.remove_at(i);
			i--;
			r++;
		}
	}
	return r;
}


int PG_Arr::mk_unique(Arr &a) {
	int r = 0, i = 0;
	while (i < a.size()) {
		for (int j = i + 1; j < a.size(); j++) {
			if (a[i] == a[j]) {
				a.remove_at(j);
				j--;
				r++;
			}
		}
		i++;
	}
	return r;
}


template <typename T>
int PG_Arr::resize_until_item(Vec<T> &v, const T &item, bool pop_found_item) {
	int i = v.rfind(item);
	if (i > -1) {
		v.resize(i + !pop_found_item);
	}
	return v.size();
}
template int PG_Arr::resize_until_item<SN>(Vec<SN> &v, const SN &item, bool pop_found_item);

int PG_Arr::_gd_resize_until_item(Arr &a, const Vrt &item, bool pop_found_item) {
	int i = a.rfind(item);
	if (i > -1) {
		a.resize(i + !pop_found_item);
	}
	return a.size();
}


//////////////////////////////////////////////////


template <typename T>
TA<T> PG_Arr::assign(const Arr &a) {
	TA<T> r;
	r.assign(a);
	return r;
}


Arr PG_Arr::_gd_assign(const Arr &from, Arr &to) {
	to.assign(from);
	return to;
}


//////////////////////////////////////////////////


template <typename T>
TA<T> PG_Arr::get_interleaved(const TA<T> &a, const T &item, bool also_if_empty) {
	TA<T> r;
	if (a.is_empty()) {
		if (also_if_empty) {
			r.append(item);
		}
		return r;
	}
	r.resize(2 * a.size() - 1);
	r.fill(item);
	for (int i : r.size()) {
		if (i % 2 == 0) {
			r[i] = a[i / 2];
		}
	}
	return r;
}


//////////////////////////////////////////////////


template <typename T>
TA<T> PG_Arr::args_to_arr(const T &arg0, const T &arg1, const T &arg2, const T &arg3, const T &arg4, const T &arg5) {
	TA<T> r;
	r.resize(6);
	r[0] = arg0;
	r[1] = arg1;
	r[2] = arg2;
	r[3] = arg3;
	r[4] = arg4;
	r[5] = arg5;
	return r;
}

template <typename T>
TA<T> PG_Arr::args_to_arr(const T &arg0, const T &arg1, const T &arg2, const T &arg3, const T &arg4) {
	TA<T> r;
	r.resize(5);
	r[0] = arg0;
	r[1] = arg1;
	r[2] = arg2;
	r[3] = arg3;
	r[4] = arg4;
	return r;
}

template <typename T>
TA<T> PG_Arr::args_to_arr(const T &arg0, const T &arg1, const T &arg2, const T &arg3) {
	TA<T> r;
	r.resize(4);
	r[0] = arg0;
	r[1] = arg1;
	r[2] = arg2;
	r[3] = arg3;
	return r;
}

template <typename T>
TA<T> PG_Arr::args_to_arr(const T &arg0, const T &arg1, const T &arg2) {
	TA<T> r;
	r.resize(3);
	r[0] = arg0;
	r[1] = arg1;
	r[2] = arg2;
	return r;
}

template <typename T>
TA<T> PG_Arr::args_to_arr(const T &arg0, const T &arg1) {
	TA<T> r;
	r.resize(2);
	r[0] = arg0;
	r[1] = arg1;
	return r;
}


//////////////////////////////////////////////////


#ifdef PG_GD_FNS
void PG_Arr::_bind_methods() {
	ClassDB::bind_static_method("PG_Arr", D_METHOD("is_arr", "v"), &PG_Arr::is_arr);
	ClassDB::bind_static_method("PG_Arr", D_METHOD("is_arr_of_str", "v"), &PG_Arr::is_arr_of_str);

	ClassDB::bind_static_method("PG_Arr", D_METHOD("to_arr", "v"), &PG_Arr::to_arr);
	ClassDB::bind_static_method("PG_Arr", D_METHOD("to_arr_of_int", "a"), &PG_Arr::to_arr_of_int);
	ClassDB::bind_static_method("PG_Arr", D_METHOD("to_arr_of_v2", "a"), &PG_Arr::to_arr_of_v2);
	ClassDB::bind_static_method("PG_Arr", D_METHOD("to_arr_of_v3", "a"), &PG_Arr::to_arr_of_v3);
	ClassDB::bind_static_method("PG_Arr", D_METHOD("to_arr_of_str", "a"), &PG_Arr::to_arr_of_str);
	ClassDB::bind_static_method("PG_Arr", D_METHOD("to_arr_of_node_3d", "a"), &PG_Arr::to_arr_of_node_3d);

	ClassDB::bind_static_method("PG_Arr", D_METHOD("get_by_idx", "a", "idx", "def"), &PG_Arr::_gd_get_by_idx, DEFVAL(Vrt::NIL));
	ClassDB::bind_static_method("PG_Arr", D_METHOD("get_by_idx_wrap", "a", "idx", "def"), &PG_Arr::_gd_get_by_idx_wrap, DEFVAL(Vrt::NIL));

	ClassDB::bind_static_method("PG_Arr", D_METHOD("last", "a", "def"), &PG_Arr::_gd_last, DEFVAL(Vrt::NIL));
	ClassDB::bind_static_method("PG_Arr", D_METHOD("penultimate", "a", "def"), &PG_Arr::_gd_penultimate, DEFVAL(Vrt::NIL));

	// TODO: CHECK IF IT WORKS WITH THIS TEMPLATE. ADD OTHERS IF SO.
	ClassDB::bind_static_method("PG_Arr", D_METHOD("find_idxs", "a", "v"), &PG_Arr::find_idxs);

	ClassDB::bind_static_method("PG_Arr", D_METHOD("has_any_in_common", "a1", "a2"), &PG_Arr::has_any_in_common);
	ClassDB::bind_static_method("PG_Arr", D_METHOD("get_approx_v_idx", "a", "v"), &PG_Arr::get_approx_v_idx);

	ClassDB::bind_static_method("PG_Arr", D_METHOD("set_last", "a", "v", "add_if_empty"), &PG_Arr::set_last, DEFVAL(true));
	ClassDB::bind_static_method("PG_Arr", D_METHOD("append_if_diff_from_last", "a", "v"), &PG_Arr::append_if_diff_from_last);

	// TODO: CHECK IF IT WORKS HERE, WHERE IT USES IMPLICIT TYPES IN TEMPLATE. ADD OTHERS IF SO.
	ClassDB::bind_static_method("PG_Arr", D_METHOD("first_f", "a", "f", "def"), &PG_Arr::_gd_first_f, DEFVAL(Vrt::NIL));

	ClassDB::bind_static_method("PG_Arr", D_METHOD("rm_all_v", "a", "v"), &PG_Arr::rm_all_v);
	//ClassDB::bind_static_method("PG_Arr", D_METHOD("rm_adj_dupes", "a"), &PG_Arr::rm_adj_dupes);
	ClassDB::bind_static_method("PG_Arr", D_METHOD("mk_unique", "a"), &PG_Arr::mk_unique);
	//ClassDB::bind_static_method("PG_Arr", D_METHOD("resize_until_item", "a", "item", "pop_found_item"), &PG_Arr::_gd_resize_until_item);
	//ClassDB::bind_static_method("PG_Arr", D_METHOD("assign", "from", "to"), &PG_Arr::_gd_assign);
}
#endif


//////////////////////////////////////////////////
//////////////////////////////////////////////////
