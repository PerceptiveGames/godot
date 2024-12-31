#include "core/object/class_db.h"
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


bool PG_Dict::is_dict(const Vrt &v) {
	return v.get_type() == Vrt::DICTIONARY;
}


//////////////////////////////////////////////////


Dict PG_Dict::to_dict(const Vrt &v) {
	return VUF::type_convert(v, Vrt::DICTIONARY);
}


template <typename K, typename V>
TD<K, V> PG_Dict::from_arr(const Arr &a, const Callable &f) {
	// TODO: Maybe replace Pair with PG_Pair.
	TD<K, V> r;
	for (const Vrt &v : a) {
		Pair<K, V> e = f.call(v);
		r[e.first] = e.second;
	}
	return r;
}

#ifdef PG_GD_FNS
Dict PG_Dict::_gd_from_arr(const Arr &a, const Callable &f) {
	Dict r;
	for (const Vrt &v : a) {
		Ref<PG_Pair> e = f.call(v);
		r[e->v1()] = e->v2();
	}
	return r;
}
#endif


template <typename DV, typename K, typename HMV>
TD<K, DV> PG_Dict::from_vmap(const VMap<K, HMV> &hm) {
	TD<K, DV> r;
	for (KV<K, HMV> kv : hm) {
		// TODO: Why asterisk before?
		//r[kv.key] = *kv.value;
		r[kv.key] = kv.value;
	}
	return r;
}


//////////////////////////////////////////////////


bool PG_Dict::idx_ok(const Dict &a, int i) {
	return i >= 0 && i < a.size();
}


template <typename K, typename V>
Pair<K, V> PG_Dict::get_by_idx(const TD<K, V> &d, int idx) {
	if (!idx_ok(d, idx)) {
		return nullptr;
	}
	return Pair<K, V>(d.get_key_at_index(idx), d.get_value_at_index(idx));
}

#ifdef PG_GD_FNS
Dict PG_Dict::_gd_get_by_idx(const Dict &d, int idx) {
	if (!idx_ok(d, idx)) {
		return Dict();
	}
	Dict r;
	r[d.get_key_at_index(idx)] = d.get_value_at_index(idx);
	return r;
}
#endif


//////////////////////////////////////////////////


template <typename K, typename V>
TD<K, V> PG_Dict::filter(const TD<K, V> &d, const Callable &f) {
	TD<K, V> r;
	for (const K &k : d) {
		if (f.call(k, d[k])) {
			r[k] = d[k];
		}
	}
	return r;
}

#ifdef PG_GD_FNS
Dict PG_Dict::_gd_filter(const Dict &d, const Callable &f) {
	Dict r;
	Arr ks = d.keys();
	for (int i = 0; i < d.size(); i++) {
		Vrt &k = ks[i];
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
