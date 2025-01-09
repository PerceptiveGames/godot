#ifndef PG_VEC_H
#define PG_VEC_H

#include "core/object/object.h"
#include "modules/pg_g1/data/pg_macros.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class Callable;
enum class Key;
class Variant;

template <typename T>
class TypedArray;

template <typename T>
class Vector;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Vec : public Object {
	GDCLASS(PG_Vec, Object);
	PG_BIND;


//////////////////////////////////////////////////


public:
	template <typename T>
	PG_INLINE static bool idx_ok(const Vector<T> &v, int idx);


//////////////////////////////////////////////////


public:
	template <typename T>
	PG_INLINE static T get_by_idx(const Vector<T> &v, int idx, T &def);

	template <typename T>
	PG_INLINE static T get_by_idx_wrap(const Vector<T> &v, int idx, T &def);


//////////////////////////////////////////////////


public:
	// DOC: Use T = *P if Array is made of Objects. Should also be able to use Ref<T>.
	template <typename T>
	static T first_f(const Vector<T> &v, const Callable &f, T &def);


//////////////////////////////////////////////////


public:
	// TODO: Maybe return a PGW.
	// TODO: Test with pointer and reference types.
	template <typename T>
	static T last(Vector<T> &v);

	// DOC: Same as Array::back() except it doesn't generate an error if array is empty.
	template <class T>
	PG_INLINE static T last(const Vector<T> &v, T &def);

	
	template <class T>
	PG_INLINE static T penultimate(const Vector<T> &v, T &def);


//////////////////////////////////////////////////


public:
	template <typename T>
	static T pop_back(Vector<T> &v);


//////////////////////////////////////////////////


public:
	template <typename T>
	static int rm_adj_dupes(Vector<T> &v);


//////////////////////////////////////////////////


public:
	template <typename T>
	static int resize_until_item(Vector<T> &v, const T &item, bool pop_found_item);

	template <typename T>
	static Vector<T> from_typed_arr(TypedArray<T> a);


//////////////////////////////////////////////////


public:
	static Vector<Key> to_arr_of_valid_keycodes(const Variant &v);


//////////////////////////////////////////////////


public:
	template <typename T>
	static Vector<T> get_interleaved(const Vector<T> &v, const T &item, bool also_if_empty = false);
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_VEC_H
