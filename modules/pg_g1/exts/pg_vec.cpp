#include "core/variant/variant.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/exts/pg_vec.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////



bool PG_Vec::is_i32a(const Vrt &v) {
	return v.get_type() == Vrt::PACKED_INT32_ARRAY;
}

bool PG_Vec::is_i64a(const Vrt &v) {
	return v.get_type() == Vrt::PACKED_INT64_ARRAY;
}


//////////////////////////////////////////////////


template <typename T>
T PG_Vec::last(Vec<T> &v) {
	if (v.is_empty()) {
		return T();
	}
	return v.get(v.size() - 1);
}
template SN PG_Vec::last(Vec<SN> &v);


//////////////////////////////////////////////////


template <typename T>
T PG_Vec::pop_back(Vec<T> &v) {
	T e = v.get(v.size() - 1);
	v.remove_at(v.size() - 1);
	return e;
}
template SN PG_Vec::pop_back(Vec<SN> &v);


//////////////////////////////////////////////////


template <typename T>
int PG_Vec::rm_adj_dupes(Vec<T> &v) {
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


#ifdef PG_GD_FNS
void PG_Vec::_bind_methods() {
	//ClassDB::bind_static_method("PG_Arr", D_METHOD("get_by_idx", "a", "idx", "def"), &PG_Arr::_gd_get_by_idx, DEFVAL(Variant::NIL));
	//ClassDB::bind_static_method("PG_Arr", D_METHOD("get_by_idx_wrap", "a", "idx", "def"), &PG_Arr::_gd_get_by_idx_wrap, DEFVAL(Variant::NIL));
	//ClassDB::bind_static_method("PG_Arr", D_METHOD("last", "a", "def"), &PG_Arr::_gd_last, DEFVAL(Variant::NIL));
	//ClassDB::bind_static_method("PG_Arr", D_METHOD("penultimate", "a", "def"), &PG_Arr::_gd_penultimate, DEFVAL(Variant::NIL));
	//ClassDB::bind_static_method("PG_Arr", D_METHOD("find_idxs", "a", "v"), &PG_Arr::find_idxs);
	//ClassDB::bind_static_method("PG_Arr", D_METHOD("has_any_in_common", "a1", "a2"), &PG_Arr::has_any_in_common);
}
#endif


//////////////////////////////////////////////////
//////////////////////////////////////////////////
