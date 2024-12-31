#ifndef PG_DICT_H
#define PG_DICT_H

#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/types/pg_typedefs.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class Callable;

template <typename K, typename V>
struct Pair;

template <typename K, typename V>
class VMap;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Dict : public RefCounted {
	GDCLASS(PG_Dict, RefCounted);
	PG_BIND;


//////////////////////////////////////////////////


public:
	PG_INLINE static bool is_dict(const Vrt &v);


//////////////////////////////////////////////////


public:
	PG_INLINE static Dict to_dict(const Vrt &v);


	// DOC: f takes a value1 as input and outputs a pair of two elements: key2 and value2.
	template <typename K, typename V>
	static TD<K, V> from_arr(const Arr &a, const Callable &f);

#ifdef PG_GD_FNS
	// DOC: f takes a variant value1 as input and outputs a Ref<PG_Pair> of two elements: key2 and value2.
	static Dict _gd_from_arr(const Arr &a, const Callable &f);
#endif


	template <typename DV, typename K, typename HMV>
	static TD<K, DV> from_vmap(const VMap<K, HMV> &hm); // NOTE: Was ref_to_dict().


//////////////////////////////////////////////////


public:
	PG_INLINE static bool idx_ok(const Dict &a, int i);


	// NOTE: There was also get_key_by_idx() and get_value_by_idx().
	template <typename K, typename V>
	static Pair<K, V> get_by_idx(const TD<K, V> &d, int idx);

#ifdef PG_GD_FNS
	static Dict _gd_get_by_idx(const Dict &d, int idx);
#endif


//////////////////////////////////////////////////


public:
	// TODO: Create a by_ref version if necessary.
	template<typename K, typename V>
	static TD<K, V> filter(const TD<K, V> &d, const Callable &f);

#ifdef PG_GD_FNS
	static Dict _gd_filter(const Dict &d, const Callable &f);
#endif
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_DICT_H
