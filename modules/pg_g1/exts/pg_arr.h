#ifndef PG_ARR_H
#define PG_ARR_H

#include "core/object/object.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "core/variant/variant.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


// TODO: Add method variants using templates where Variant is used.
// Do not delete existing Variant ones.
// Also do that in other classes.


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class Array;
class Callable;
class Node3D;
enum class Key;

template <typename K, typename V>
struct Pair;

template <typename T>
class TypedArray;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Arr : public Object {
	GDCLASS(PG_Arr, Object);
	PG_BIND;


//////////////////////////////////////////////////


public:
	PG_INLINE static bool is_arr(const Variant &v);


//////////////////////////////////////////////////


public:
	PG_INLINE static Array to_arr(const Variant &v);

	PG_INLINE static Array from_pair(const Pair<Variant, Variant> &v);


//////////////////////////////////////////////////


public:
	PG_INLINE static bool idx_ok(const Array &a, int i);


//////////////////////////////////////////////////


public:
	static Variant get_by_idx(const Array &a, int idx, const Variant &def = Variant::NIL);

	static Variant get_by_idx_wrap(const Array &a, int idx, const Variant &def = Variant::NIL);


//////////////////////////////////////////////////


public:
	// DOC: Same as Array::back() except it doesn't generate an error if array is empty.
	static Variant last(const Array &a, const Variant &def = Variant::NIL);

	static Variant penultimate(const Array &a, const Variant &def = Variant::NIL);


//////////////////////////////////////////////////


public:
	static TypedArray<int> find_idxs(const Array &a, const Variant &v);

	static bool has_any_in_common(const Array &a1, const Array &a2);

	// DOC: Returns the index of the first value found in 'a' that is approx equal to 'v', or -1.
	static int get_approx_v_idx(const Array &a, const Variant &v);


//////////////////////////////////////////////////


public:
	static bool set_last(Array &a, const Variant &v, bool add_if_empty = true);

#ifdef PG_GD_FNS
	// TODO: Add non-GD version that takes a ref to a (&a) instead.
	// Ref to a is not accepted in GD functions by the compiler.
	static bool _gd_set_last(Array a, const Variant &v, bool add_if_empty = true);
#endif

	static bool append_if_diff_from_last(Array &a, const Variant &v);

#ifdef PG_GD_FNS
	static bool _gd_append_if_diff_from_last(Array a, const Variant &v);
#endif


//////////////////////////////////////////////////


public:
	static Variant first_f(const Array &a, const Callable &f, const Variant &def = Variant::NIL);


//////////////////////////////////////////////////


public:
	static int rm_all_v(Array &a, const Variant &v);

#ifdef PG_GD_FNS
	static int _gd_rm_all_v(Array a, const Variant &v);
#endif

	static int rm_adj_dupes(Array &a);

#ifdef PG_GD_FNS
	static int _gd_rm_adj_dupes(Array a);
#endif

	// DOC: Returns the number of items removed.
	static int mk_unique(Array &a);

#ifdef PG_GD_FNS
	static int _gd_mk_unique(Array a);
#endif

	// NOTE: Was 'pop_back_until_found()'.
	static int resize_until_item(Array &a, const Variant &item, bool pop_found_item);

#ifdef PG_GD_FNS
	static int _gd_resize_until_item(Array a, const Variant &item, bool pop_found_item);
#endif


//////////////////////////////////////////////////


public:
	template <typename T>
	static TypedArray<T> assign(const Array &a) {
		TypedArray<T> r;
		r.assign(a);
		return r;
	}


	// DOC: Has _gd prefix to differentiate from native method and to be able to bind to GD.
	// DOC: It can still be used in C++.
	static Array _gd_assign(const Array &from, Array to);


//////////////////////////////////////////////////


public:
	static Array get_interleaved(const Array &a, const Variant &item, bool also_if_empty = false);


//////////////////////////////////////////////////


public:
	template <typename T, typename... P>
	TypedArray<T> args_to_arr(TypedArray<T> &a, const T &v); 

	template <typename T, typename... P>
	TypedArray<T> args_to_arr(TypedArray<T> &a, const T &v, P... args); 

	template <typename T, typename... P>
	TypedArray<T> args_to_arr(P... args);
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_ARR_H
