#ifndef PG_V2_H
#define PG_V2_H

#include "core/object/object.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/types/pg_typedefs.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class Array;
class Vector2;
class Vector3;

template <typename T>
class TypedArray;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_V2 : public Object {
	GDCLASS(PG_V2, Object);
	PG_BIND;


//////////////////////////////////////////////////


public:
	static Vector2 &neg_x(Vector2 &v);
	static Vector2 &neg_y(Vector2 &v);


//////////////////////////////////////////////////


public:
	static Vector2 &set_x(Vector2 &v, const float x);
	static Vector2 &set_y(Vector2 &v, const float y);


//////////////////////////////////////////////////


public:
	static Vector2 set_from_v3_xy(Vector3 &xy);
	static Vector2 set_from_v3_xz(Vector3 &xz);
	static Vector2 set_from_v3_yz(Vector3 &yz);


//////////////////////////////////////////////////


public:
	static Vector2 sum(const TypedArray<Vector2> &a);
	static Vector2 avg(const TypedArray<Vector2> &a);


//////////////////////////////////////////////////


public:
	PG_INLINE static TypedArray<Vector2> to_arr_of_v2(const Array &a);
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_V2_H
