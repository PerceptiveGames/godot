#include "core/math/math_funcs.h"
#include "core/object/class_db.h"
#include "core/os/keyboard.h"
#include "core/string/string_name.h"
#include "core/string/ustring.h"
#include "core/templates/pair.h"
#include "core/templates/vector.h"
#include "core/variant/array.h"
#include "core/variant/callable.h"
#include "core/variant/typed_array.h"
#include "core/variant/variant.h"
#include "core/variant/variant_utility.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/exts/pg_arr.h"
#include "modules/pg_g1/exts/pg_str.h"
#include "modules/pg_g1/user/pg_input.h"
#include "scene/3d/node_3d.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


// DOC: GD functions cannot take 'Array &a' as argument.
// Needs to be either 'const Array &a' or 'Array a'.


//////////////////////////////////////////////////
//////////////////////////////////////////////////


bool PG_Arr::is_arr(const Variant &v) {
	return v.get_type() == Variant::ARRAY;
}


//////////////////////////////////////////////////


Array PG_Arr::to_arr(const Variant &v) {
	return VariantUtilityFunctions::type_convert(v, Variant::ARRAY);
}


Array PG_Arr::from_pair(const Pair<Variant, Variant> &v) {
	Array r;
	r.append(v.first);
	r.append(v.second);
	return r;
}


template <typename T>
Array PG_Arr::from_vec(Vector<T> v) {
	Array r;
	for (T e : v) {
		r.append(e);
	}
	return r;
}


//////////////////////////////////////////////////


bool PG_Arr::idx_ok(const Array &a, int i) {
	return i >= 0 && i < a.size();
}


//////////////////////////////////////////////////


Variant PG_Arr::get_by_idx(const Array &a, int idx, const Variant &def) {
	return PG_Arr::idx_ok(a, idx) ? a[idx] : def;
}


Variant PG_Arr::get_by_idx_wrap(const Array &a, int idx, const Variant &def) {
	return !a.is_empty() ? a[idx % a.size()] : def;
}


//////////////////////////////////////////////////


Variant PG_Arr::last(const Array &a, const Variant &def) {
	return !a.is_empty() ? a[-1] : def;
}


Variant PG_Arr::penultimate(const Array &a, const Variant &def) {
	return a.size() > 1 ? a[-2] : def;
}


//////////////////////////////////////////////////


TypedArray<int> PG_Arr::find_idxs(const Array &a, const Variant &v) {
	TypedArray<int> r = TypedArray<int>();
	for (int i = 0; i < a.size(); i++) {
		if (a[i] == v) {
			r.append(i);
		}
	}
	return r;
}


bool PG_Arr::has_any_in_common(const Array &a1, const Array &a2) {
	for (const Variant &e : a1) {
		if (a2.has(e)) {
			return true;
		}
	}
	return false;
}


int PG_Arr::get_approx_v_idx(const Array &a, const Variant &v) {
	for (int i = 0; i < a.size(); i++) {
		if (Math::is_equal_approx(double(a[i]), double(v))) {
			return i;
		}
	}
	return -1;
}


//////////////////////////////////////////////////


bool PG_Arr::set_last(Array &a, const Variant &v, bool add_if_empty) {
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


#ifdef PG_GD_FNS
bool PG_Arr::_gd_set_last(Array a, const Variant &v, bool add_if_empty) {
	return set_last(a, v, add_if_empty);
}
#endif


bool PG_Arr::append_if_diff_from_last(Array &a, const Variant &v) {
	if (a.back() != v) {
		a.append(v);
		return true;
	}
	return false;
}


#ifdef PG_GD_FNS
bool PG_Arr::_gd_append_if_diff_from_last(Array a, const Variant &v) {
	return append_if_diff_from_last(a, v);
}
#endif


//////////////////////////////////////////////////


Variant PG_Arr::first_f(const Array &a, const Callable &f, const Variant &def) {
	for (const Variant &e : a) {
		if (f.call(e)) {
			return e;
		}
	}
	return def;
}


//////////////////////////////////////////////////


int PG_Arr::rm_all_v(Array &a, const Variant &v) {
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


#ifdef PG_GD_FNS
int PG_Arr::_gd_rm_all_v(Array a, const Variant &v) {
	return rm_all_v(a, v);
}
#endif


int PG_Arr::rm_adj_dupes(Array &a) {
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


#ifdef PG_GD_FNS
int PG_Arr::_gd_rm_adj_dupes(Array a) {
	return rm_adj_dupes(a);
}
#endif


int PG_Arr::mk_unique(Array &a) {
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


#ifdef PG_GD_FNS
int PG_Arr::_gd_mk_unique(Array a) {
	return mk_unique(a);
}
#endif


int PG_Arr::resize_until_item(Array &a, const Variant &item, bool pop_found_item) {
	int i = a.rfind(item);
	if (i > -1) {
		a.resize(i + !pop_found_item);
	}
	return a.size();
}


#ifdef PG_GD_FNS
int PG_Arr::_gd_resize_until_item(Array a, const Variant &item, bool pop_found_item) {
	return resize_until_item(a, item, pop_found_item);
}
#endif


//////////////////////////////////////////////////


Array PG_Arr::_gd_assign(const Array &from, Array to) {
	to.assign(from);
	return to;
	return from;
}


//////////////////////////////////////////////////


Array PG_Arr::get_interleaved(const Array &a, const Variant &item, bool also_if_empty) {
	Array r;
	if (a.is_empty()) {
		if (also_if_empty) {
			r.append(item);
		}
		return r;
	}
	r.resize(2 * a.size() - 1);
	r.fill(item);
	for (int i = 0; i < r.size(); ++i) {
		if (i % 2 == 0) {
			r[i] = a[i / 2];
		}
	}
	return r;
}


//////////////////////////////////////////////////


void PG_Arr::_bind_methods() {
#ifdef PG_GD_FNS
	ClassDB::bind_static_method("PG_Arr", D_METHOD("is_arr", "v"), &PG_Arr::is_arr);

	ClassDB::bind_static_method("PG_Arr", D_METHOD("to_arr", "v"), &PG_Arr::to_arr);

	ClassDB::bind_static_method("PG_Arr", D_METHOD("get_by_idx", "a", "idx", "def"), &PG_Arr::get_by_idx, DEFVAL(Variant::NIL));
	ClassDB::bind_static_method("PG_Arr", D_METHOD("get_by_idx_wrap", "a", "idx", "def"), &PG_Arr::get_by_idx_wrap, DEFVAL(Variant::NIL));

	ClassDB::bind_static_method("PG_Arr", D_METHOD("last", "a", "def"), &PG_Arr::last, DEFVAL(Variant::NIL));
	ClassDB::bind_static_method("PG_Arr", D_METHOD("penultimate", "a", "def"), &PG_Arr::penultimate, DEFVAL(Variant::NIL));

	ClassDB::bind_static_method("PG_Arr", D_METHOD("find_idxs", "a", "v"), &PG_Arr::find_idxs);
	ClassDB::bind_static_method("PG_Arr", D_METHOD("has_any_in_common", "a1", "a2"), &PG_Arr::has_any_in_common);
	ClassDB::bind_static_method("PG_Arr", D_METHOD("get_approx_v_idx", "a", "v"), &PG_Arr::get_approx_v_idx);

	ClassDB::bind_static_method("PG_Arr", D_METHOD("set_last", "a", "v", "add_if_empty"), &PG_Arr::_gd_set_last, DEFVAL(true));
	ClassDB::bind_static_method("PG_Arr", D_METHOD("append_if_diff_from_last", "a", "v"), &PG_Arr::_gd_append_if_diff_from_last);

	ClassDB::bind_static_method("PG_Arr", D_METHOD("first_f", "a", "f", "def"), &PG_Arr::first_f, DEFVAL(Variant::NIL));

	ClassDB::bind_static_method("PG_Arr", D_METHOD("rm_all_v", "a", "v"), &PG_Arr::_gd_rm_all_v);
	ClassDB::bind_static_method("PG_Arr", D_METHOD("rm_adj_dupes", "a"), &PG_Arr::_gd_rm_adj_dupes);
	ClassDB::bind_static_method("PG_Arr", D_METHOD("mk_unique", "a"), &PG_Arr::_gd_mk_unique);
	ClassDB::bind_static_method("PG_Arr", D_METHOD("resize_until_item", "a", "item", "pop_found_item"), &PG_Arr::_gd_resize_until_item);
	ClassDB::bind_static_method("PG_Arr", D_METHOD("assign", "from", "to"), &PG_Arr::_gd_assign);
	ClassDB::bind_static_method("PG_Arr", D_METHOD("assign2", "from"), &PG_Arr::_gd_assign);

	ClassDB::bind_static_method("PG_Arr", D_METHOD("get_interleaved", "a", "item", "also_if_empty"), &PG_Arr::get_interleaved, DEFVAL(false));
#endif
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
