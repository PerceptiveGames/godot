#include "core/math/vector2.h"
#include "core/math/vector3.h"
#include "core/object/class_db.h"
#include "core/variant/typed_array.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/exts/pg_v3.h"
#include "modules/pg_g1/types/pg_typedefs.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


V3 &PG_V3::neg_x(V3 &v) {
	v.x = -v.x;
	return v;
}


V3 &PG_V3::neg_y(V3 &v) {
	v.y = -v.y;
	return v;
}


V3 &PG_V3::neg_z(V3 &v) {
	v.z = -v.z;
	return v;
}


V3 &PG_V3::set_x(V3 &v, const float x) {
	v.x = x;
	return v;
}


V3 &PG_V3::set_y(V3 &v, const float y) {
	v.y = y;
	return v;
}


V3 &PG_V3::set_z(V3 &v, const float z) {
	v.z = z;
	return v;
}


//////////////////////////////////////////////////


V3 PG_V3::set_xz_from_v2(V2 &xz, const float y) {
	return V3(xz.x, y, xz.y);
}


V3 PG_V3::set_yz_from_v2(V2 &yz, const float x) {
	return V3(x, yz.x, yz.y);
}


V3 PG_V3::set_zy_from_v2(V2 &zy, const float x) {
	return V3(x, zy.y, zy.x);
}


//////////////////////////////////////////////////


V3 PG_V3::sum(const TA<V3> &a) {
	V3 r;
	for (const V3 &v : a) {
		r += v;
	}
	return r;
}


V3 PG_V3::avg(const TA<V3> &a) {
	return sum(a) / a.size();
}


// DOC : Vertices must be clockwise
// DOC : https://computergraphics.stackexchange.com/a/4032
V3 PG_V3::nrm(const V3 &p0, const V3 &p1, const V3 &p2) {
	return (p2 - p0).cross(p1 - p0).normalized();
}


//////////////////////////////////////////////////


//V3 &V3::operator+=(const V3 &p_v) {
//	x += p_v.x;
//	y += p_v.y;
//	z += p_v.z;
//	return *this;
//}


//////////////////////////////////////////////////


#ifdef PG_GD_FNS
void PG_V3::_bind_methods() {
	// TODO: UNCOMMENT AND COMPILE.
	//ClassDB::bind_static_method("PG_V3", D_METHOD("set_x", "v", "x"), &PG_V3::set_x);
	//ClassDB::bind_static_method("PG_V3", D_METHOD("set_y", "v", "y"), &PG_V3::set_y);
	//ClassDB::bind_static_method("PG_V3", D_METHOD("set_z", "v", "z"), &PG_V3::set_z);

	//ClassDB::bind_static_method("PG_V3", D_METHOD("set_xz_from_v2", "xz", "y"), &PG_V3::set_xz_from_v2);
	//ClassDB::bind_static_method("PG_V3", D_METHOD("set_yz_from_v2", "yz", "x"), &PG_V3::set_yz_from_v2);
	//ClassDB::bind_static_method("PG_V3", D_METHOD("set_zy_from_v2", "zy", "x"), &PG_V3::set_zy_from_v2);

	//ClassDB::bind_static_method("PG_V3", D_METHOD("sum", "a"), &PG_V3::sum);
	//ClassDB::bind_static_method("PG_V3", D_METHOD("avg", "a"), &PG_V3::avg);
	//ClassDB::bind_static_method("PG_V3", D_METHOD("nrm", "p0", "p1", "p2"), &PG_V3::nrm);
}
#endif


//////////////////////////////////////////////////
//////////////////////////////////////////////////
