#ifndef PG_DICT_H
#define PG_DICT_H

#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "modules/pg_g1/data/pg_macros.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class Array;
class Callable;
class Dictionary;
class Variant;

template <typename K, typename V>
class TypedDictionary;

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
	PG_INLINE static bool is_dict(const Variant &v);


//////////////////////////////////////////////////


public:
	PG_INLINE static Dictionary to_dict(const Variant &v);

	// DOC: f takes a value1 as input and outputs a pair of two elements: key2 and value2.
	template <typename K, typename V>
	static TypedDictionary<K, V> from_arr(const Array &a, const Callable &f);

#ifdef PG_GD_FNS
	// DOC: f takes a variant value1 as input and outputs a Ref<PG_Pair> of two elements: key2 and value2.
	static Dictionary _gd_from_arr(const Array &a, const Callable &f);
#endif

	template <typename DV, typename K, typename HMV>
	static TypedDictionary<K, DV> from_vmap(const VMap<K, HMV> &hm); // NOTE: Was ref_to_dict().


//////////////////////////////////////////////////


public:
	PG_INLINE static bool idx_ok(const Dictionary &a, int i);

	// NOTE: There was also get_key_by_idx() and get_value_by_idx().
	template <typename K, typename V>
	static Pair<K, V> get_by_idx(const TypedDictionary<K, V> &d, int i);

#ifdef PG_GD_FNS
	static Dictionary _gd_get_by_idx(const Dictionary &d, int i);
#endif


//////////////////////////////////////////////////


public:
	// TODO: Create a by_ref version if necessary.
	template<typename K, typename V>
	static TypedDictionary<K, V> filter(const TypedDictionary<K, V> &d, const Callable &f);

#ifdef PG_GD_FNS
	static Dictionary _gd_filter(const Dictionary &d, const Callable &f);
#endif
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_DICT_H
