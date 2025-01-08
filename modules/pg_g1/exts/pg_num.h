#ifndef PG_NUM_H
#define PG_NUM_H

#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "modules/pg_g1/data/pg_macros.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class Array;
class RandomNumberGenerator;
class String;
class Variant;

template <typename T>
class TypedArray;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Num : public Object {
	GDCLASS(PG_Num, Object);
	PG_BIND;


//////////////////////////////////////////////////


public:
	PG_INLINE static bool is_int(const Variant &v);

	static bool is_only_digits(String s);

	static bool is_int_in_rng(Variant v, int min_incl, int max_incl);


//////////////////////////////////////////////////

	
public:
	PG_INLINE static int to_int(const Variant &v);

	// DOC: Returns -1 if v is not greater than or equal to i.
	PG_INLINE static int to_int_if_gte(const Variant &v, const int i);

	// DOC: Returns -1 if v is not between min_incl and max_incl, inclusive.
	PG_INLINE static int to_int_if_bw(const Variant &v, const int min_incl, const int max_incl);


//////////////////////////////////////////////////
	

public:
	// DOC: Named so because PackedInt32Array is a Vector<int32> internally.
	PG_INLINE static bool is_i32vec(const Variant &v);

	// DOC: Named so because PackedInt64Array is a Vector<int64> internally.
	PG_INLINE static bool is_i64vec(const Variant &v);


//////////////////////////////////////////////////


public:
	PG_INLINE static TypedArray<int> to_arr_of_int(const Array &a);


//////////////////////////////////////////////////


protected:
	static Ref<RandomNumberGenerator> _rng;


public:
	static Ref<RandomNumberGenerator> const get_rng();

	static int get_rnd_int(int min_incl, int max_incl);


//////////////////////////////////////////////////


public:
	static void init();
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_NUM_H
