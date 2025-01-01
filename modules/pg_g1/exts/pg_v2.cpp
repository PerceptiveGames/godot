#include "core/math/vector2.h"
#include "core/math/vector3.h"
#include "core/object/class_db.h"
#include "core/variant/array.h"
#include "core/variant/typed_array.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/exts/pg_v2.h"
#include "pg_arr.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


Vector2 &PG_V2::neg_x(Vector2 &v) {
	v.x = -v.x;
	return v;
}


Vector2 &PG_V2::neg_y(Vector2 &v) {
	v.y = -v.y;
	return v;
}


//////////////////////////////////////////////////


Vector2 &PG_V2::set_x(Vector2 &v, const float x) {
	v.x = x;
	return v;
}


Vector2 &PG_V2::set_y(Vector2 &v, const float y) {
	v.y = y;
	return v;
}


//////////////////////////////////////////////////


Vector2 PG_V2::set_from_v3_xy(Vector3 &xy) {
	return Vector2(xy.x, xy.y);
}


Vector2 PG_V2::set_from_v3_xz(Vector3 &xz) {
	return Vector2(xz.x, xz.z);
}


Vector2 PG_V2::set_from_v3_yz(Vector3 &yz) {
	return Vector2(yz.y, yz.z);
}


//////////////////////////////////////////////////


Vector2 PG_V2::sum(const TypedArray<Vector2> &a) {
	Vector2 r;
	for (const Vector2 &v : a) {
		r += v;
	}
	return r;
}


Vector2 PG_V2::avg(const TypedArray<Vector2> &a) {
	return sum(a) / a.size();
}


//////////////////////////////////////////////////


TypedArray<Vector2> PG_V2::to_arr_of_v2(const Array &a) {
	return PG_Arr::assign<Vector2>(a);
}


//////////////////////////////////////////////////


void PG_V2::_bind_methods() {
#ifdef PG_GD_FNS
	// TODO: UNCOMMENT AND FIX COMPILATION ERROR.
	//ClassDB::bind_static_method("PG_V2", D_METHOD("set_x", "v", "x"), &PG_V2::set_x);
	//ClassDB::bind_static_method("PG_V2", D_METHOD("set_y", "v", "y"), &PG_V2::set_y);

	//ClassDB::bind_static_method("PG_V2", D_METHOD("set_from_v3_xy", "xy"), &PG_V2::set_from_v3_xy);
	//ClassDB::bind_static_method("PG_V2", D_METHOD("set_from_v3_xz", "xz"), &PG_V2::set_from_v3_xz);
	//ClassDB::bind_static_method("PG_V2", D_METHOD("set_from_v3_yz", "yz"), &PG_V2::set_from_v3_yz);

	//ClassDB::bind_static_method("PG_V2", D_METHOD("sum", "a"), &PG_V2::sum);
	//ClassDB::bind_static_method("PG_V2", D_METHOD("avg", "a"), &PG_V2::avg);
#endif
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
