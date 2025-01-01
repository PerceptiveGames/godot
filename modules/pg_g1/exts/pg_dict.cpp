#include "core/object/class_db.h"
#include "core/object/ref_counted.h"
#include "core/templates/pair.h"
#include "core/templates/vmap.h"
#include "core/variant/callable.h"
#include "core/variant/dictionary.h"
#include "core/variant/variant.h"
#include "core/variant/variant_utility.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/exts/pg_dict.h"
#include "modules/pg_g1/types/pg_pair.h"
#include "modules/pg_g1/types/pg_typedefs.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


bool PG_Dict::is_dict(const Variant &v) {
	return v.get_type() == Variant::DICTIONARY;
}


//////////////////////////////////////////////////


Dictionary PG_Dict::to_dict(const Variant &v) {
	return VariantUtilityFunctions::type_convert(v, Variant::DICTIONARY);
}


template <typename K, typename V>
TypedDictionary<K, V> PG_Dict::from_arr(const Array &a, const Callable &f) {
	// TODO: Maybe replace Pair with PG_Pair.
	TypedDictionary<K, V> r;
	for (const Variant &v : a) {
		Pair<K, V> e = f.call(v);
		r[e.first] = e.second;
	}
	return r;
}


#ifdef PG_GD_FNS
Dictionary PG_Dict::_gd_from_arr(const Array &a, const Callable &f) {
	Dictionary r;
	for (const Variant &v : a) {
		Ref<PG_Pair> e = f.call(v);
		r[e->v1()] = e->v2();
	}
	return r;
}
#endif


template <typename DV, typename K, typename HMV>
TypedDictionary<K, DV> PG_Dict::from_vmap(const VMap<K, HMV> &hm) {
	TypedDictionary<K, DV> r;
	for (KeyValue<K, HMV> kv : hm) {
		// TODO: Why asterisk before?
		//r[kv.key] = *kv.value;
		r[kv.key] = kv.value;
	}
	return r;
}


//////////////////////////////////////////////////


bool PG_Dict::idx_ok(const Dictionary &a, int i) {
	return i >= 0 && i < a.size();
}


template <typename K, typename V>
Pair<K, V> PG_Dict::get_by_idx(const TypedDictionary<K, V> &d, int idx) {
	if (!idx_ok(d, idx)) {
		return nullptr;
	}
	return Pair<K, V>(d.get_key_at_index(idx), d.get_value_at_index(idx));
}


#ifdef PG_GD_FNS
Dictionary PG_Dict::_gd_get_by_idx(const Dictionary &d, int idx) {
	if (!idx_ok(d, idx)) {
		return Dictionary();
	}
	Dictionary r;
	r[d.get_key_at_index(idx)] = d.get_value_at_index(idx);
	return r;
}
#endif


//////////////////////////////////////////////////


template <typename K, typename V>
TypedDictionary<K, V> PG_Dict::filter(const TypedDictionary<K, V> &d, const Callable &f) {
	TypedDictionary<K, V> r;
	for (const K &k : d) {
		if (f.call(k, d[k])) {
			r[k] = d[k];
		}
	}
	return r;
}


#ifdef PG_GD_FNS
Dictionary PG_Dict::_gd_filter(const Dictionary &d, const Callable &f) {
	Dictionary r;
	Array ks = d.keys();
	for (int i = 0; i < d.size(); i++) {
		Variant &k = ks[i];
		if (f.call(k, d[k])) {
			r[k] = d[k];
		}
	}
	return r;
}
#endif


//////////////////////////////////////////////////


#ifdef PG_GD_FNS
void PG_Dict::_bind_methods() {
	ClassDB::bind_static_method("PG_Dict", D_METHOD("from_arr", "a", "f"), &PG_Dict::_gd_from_arr);
	ClassDB::bind_static_method("PG_Dict", D_METHOD("get_by_idx", "a", "idx"), &PG_Dict::_gd_get_by_idx);
	ClassDB::bind_static_method("PG_Dict", D_METHOD("filter", "d", "f"), &PG_Dict::_gd_filter);
}
#endif


//////////////////////////////////////////////////
//////////////////////////////////////////////////
