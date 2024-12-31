#ifndef PG_VEC_H
#define PG_VEC_H

#include "core/object/object.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/types/pg_typedefs.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Vec : public Object {
	GDCLASS(PG_Vec, Object);
	PG_BIND;


//////////////////////////////////////////////////


public:
	PG_INLINE static bool is_i32a(const Vrt &v);


	PG_INLINE static bool is_i64a(const Vrt &v);


//////////////////////////////////////////////////


public:
	// TODO: Maybe return a PGW.
	// TODO: Test with pointer and reference types.
	template <typename T>
	static T last(Vec<T> &v);


//////////////////////////////////////////////////


public:
	template <typename T>
	static T pop_back(Vec<T> &v);


//////////////////////////////////////////////////


public:
	template <typename T>
	static int rm_adj_dupes(Vec<T> &v);
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_VEC_H
