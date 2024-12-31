#include "core/math/vector2.h"
#include "core/math/vector3.h"
#include "core/object/class_db.h"
#include "core/variant/typed_array.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/exts/pg_v2.h"
#include "modules/pg_g1/types/pg_typedefs.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


V2 &PG_V2::neg_x(V2 &v) {
	v.x = -v.x;
	return v;
}


V2 &PG_V2::neg_y(V2 &v) {
	v.y = -v.y;
	return v;
}


//////////////////////////////////////////////////


V2 &PG_V2::set_x(V2 &v, const float x) {
	v.x = x;
	return v;
}


V2 &PG_V2::set_y(V2 &v, const float y) {
	v.y = y;
	return v;
}


//////////////////////////////////////////////////


V2 PG_V2::set_from_v3_xy(V3 &xy) {
	return V2(xy.x, xy.y);
}


V2 PG_V2::set_from_v3_xz(V3 &xz) {
	return V2(xz.x, xz.z);
}


V2 PG_V2::set_from_v3_yz(V3 &yz) {
	return V2(yz.y, yz.z);
}


//////////////////////////////////////////////////


V2 PG_V2::sum(const TA<V2> &a) {
	V2 r;
	for (const V2 &v : a) {
		r += v;
	}
	return r;
}


V2 PG_V2::avg(const TA<V2> &a) {
	return sum(a) / a.size();
}


//////////////////////////////////////////////////


#ifdef PG_GD_FNS
void PG_V2::_bind_methods() {
	// TODO: UNCOMMENT AND FIX COMPILATION ERROR.
	//ClassDB::bind_static_method("PG_V2", D_METHOD("set_x", "v", "x"), &PG_V2::set_x);
	//ClassDB::bind_static_method("PG_V2", D_METHOD("set_y", "v", "y"), &PG_V2::set_y);

	//ClassDB::bind_static_method("PG_V2", D_METHOD("set_from_v3_xy", "xy"), &PG_V2::set_from_v3_xy);
	//ClassDB::bind_static_method("PG_V2", D_METHOD("set_from_v3_xz", "xz"), &PG_V2::set_from_v3_xz);
	//ClassDB::bind_static_method("PG_V2", D_METHOD("set_from_v3_yz", "yz"), &PG_V2::set_from_v3_yz);

	//ClassDB::bind_static_method("PG_V2", D_METHOD("sum", "a"), &PG_V2::sum);
	//ClassDB::bind_static_method("PG_V2", D_METHOD("avg", "a"), &PG_V2::avg);
}
#endif


//////////////////////////////////////////////////
//////////////////////////////////////////////////
