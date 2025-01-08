#ifndef PG_V3_H
#define PG_V3_H

#include "core/object/object.h"
#include "modules/pg_g1/data/pg_macros.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class Array;
struct Vector2;
struct Vector3;

template <typename T>
class TypedArray;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_V3 : public Object {
	GDCLASS(PG_V3, Object);
	PG_BIND;


//////////////////////////////////////////////////


public:
	static Vector3 &neg_x(Vector3 &v);
	static Vector3 &neg_y(Vector3 &v);
	static Vector3 &neg_z(Vector3 &v);


//////////////////////////////////////////////////


public:
	static Vector3 &set_x(Vector3 &v, const float x);
	static Vector3 &set_y(Vector3 &v, const float y);
	static Vector3 &set_z(Vector3 &v, const float z);


//////////////////////////////////////////////////


public:
	static Vector3 set_xz_from_v2(Vector2 &xz, const float y);
#ifdef PG_GD_FNS
	static Vector3 _gd_set_xz_from_v2(Vector2 xz, const float y);
#endif

	static Vector3 set_yz_from_v2(Vector2 &yz, const float x);
#ifdef PG_GD_FNS
	static Vector3 _gd_set_yz_from_v2(Vector2 yz, const float x);
#endif

	static Vector3 set_zy_from_v2(Vector2 &zy, const float x);
#ifdef PG_GD_FNS
	static Vector3 _gd_set_zy_from_v2(Vector2 zy, const float x);
#endif


//////////////////////////////////////////////////


public:
	static Vector3 sum(const TypedArray<Vector3> &a);
	static Vector3 avg(const TypedArray<Vector3> &a);
	static Vector3 nrm(const Vector3 &p0, const Vector3 &p1, const Vector3 &p2);


//////////////////////////////////////////////////


public:
	PG_INLINE static TypedArray<Vector3> to_arr_of_v3(const Array &a);
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_V3_H
