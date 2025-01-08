#include "core/math/vector2.h"
#include "core/math/vector3.h"
#include "core/object/class_db.h"
#include "core/variant/array.h"
#include "core/variant/typed_array.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/exts/pg_arr.h"
#include "modules/pg_g1/exts/pg_v3.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


Vector3 &PG_V3::neg_x(Vector3 &v) {
	v.x = -v.x;
	return v;
}


Vector3 &PG_V3::neg_y(Vector3 &v) {
	v.y = -v.y;
	return v;
}


Vector3 &PG_V3::neg_z(Vector3 &v) {
	v.z = -v.z;
	return v;
}


Vector3 &PG_V3::set_x(Vector3 &v, const float x) {
	v.x = x;
	return v;
}


Vector3 &PG_V3::set_y(Vector3 &v, const float y) {
	v.y = y;
	return v;
}


Vector3 &PG_V3::set_z(Vector3 &v, const float z) {
	v.z = z;
	return v;
}


//////////////////////////////////////////////////


Vector3 PG_V3::set_xz_from_v2(Vector2 &xz, const float y) {
	return Vector3(xz.x, y, xz.y);
}


#ifdef PG_GD_FNS
Vector3 PG_V3::_gd_set_xz_from_v2(Vector2 xz, const float y) {
	return Vector3(xz.x, y, xz.y);
}
#endif


Vector3 PG_V3::set_yz_from_v2(Vector2 &yz, const float x) {
	return Vector3(x, yz.x, yz.y);
}


#ifdef PG_GD_FNS
Vector3 PG_V3::_gd_set_yz_from_v2(Vector2 yz, const float x) {
	return Vector3(x, yz.x, yz.y);
}
#endif


Vector3 PG_V3::set_zy_from_v2(Vector2 &zy, const float x) {
	return Vector3(x, zy.y, zy.x);
}


#ifdef PG_GD_FNS
Vector3 PG_V3::_gd_set_zy_from_v2(Vector2 zy, const float x) {
	return Vector3(x, zy.y, zy.x);
}
#endif


//////////////////////////////////////////////////


Vector3 PG_V3::sum(const TypedArray<Vector3> &a) {
	Vector3 r;
	for (const Vector3 &v : a) {
		r += v;
	}
	return r;
}


Vector3 PG_V3::avg(const TypedArray<Vector3> &a) {
	return sum(a) / a.size();
}


// DOC : Vertices must be clockwise
// DOC : https://computergraphics.stackexchange.com/a/4032
Vector3 PG_V3::nrm(const Vector3 &p0, const Vector3 &p1, const Vector3 &p2) {
	return (p2 - p0).cross(p1 - p0).normalized();
}


//////////////////////////////////////////////////


TypedArray<Vector3> PG_V3::to_arr_of_v3(const Array &a) {
	return PG_Arr::assign<Vector3>(a);
}


//////////////////////////////////////////////////


//Vector3 &Vector3::operator+=(const Vector3 &p_v) {
//	x += p_v.x;
//	y += p_v.y;
//	z += p_v.z;
//	return *this;
//}


//////////////////////////////////////////////////


void PG_V3::_bind_methods() {
#ifdef PG_GD_FNS
	ClassDB::bind_static_method("PG_V3", D_METHOD("set_xz_from_v2", "xz", "y"), &PG_V3::_gd_set_xz_from_v2);
	ClassDB::bind_static_method("PG_V3", D_METHOD("set_yz_from_v2", "yz", "x"), &PG_V3::_gd_set_yz_from_v2);
	ClassDB::bind_static_method("PG_V3", D_METHOD("set_zy_from_v2", "zy", "x"), &PG_V3::_gd_set_zy_from_v2);

	ClassDB::bind_static_method("PG_V3", D_METHOD("sum", "a"), &PG_V3::sum);
	ClassDB::bind_static_method("PG_V3", D_METHOD("avg", "a"), &PG_V3::avg);
	ClassDB::bind_static_method("PG_V3", D_METHOD("nrm", "p0", "p1", "p2"), &PG_V3::nrm);
#endif
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
