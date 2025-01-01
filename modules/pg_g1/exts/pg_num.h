#ifndef PG_NUM_H
#define PG_NUM_H

#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/types/pg_typedefs.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class RandomNumberGenerator;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Num : public Object {
	GDCLASS(PG_Num, Object);
	PG_BIND;


//////////////////////////////////////////////////


public:
	PG_INLINE static bool is_int(const Vrt &v);


	static bool is_only_digits(Str s);


	static bool is_int_in_rng(Vrt v, int min_incl, int max_incl);


//////////////////////////////////////////////////

	
public:
	PG_INLINE static int to_int(const Vrt &v);


	// DOC: Returns -1 if v is not greater than or equal to i.
	PG_INLINE static int to_int_if_gte(const Vrt &v, const int i);


	// DOC: Returns -1 if v is not between min_incl and max_incl, inclusive.
	PG_INLINE static int to_int_if_bw(const Vrt &v, const int min_incl, const int max_incl);


//////////////////////////////////////////////////


	PG_INLINE static TA<int> to_arr_of_int(const Arr &a);


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
