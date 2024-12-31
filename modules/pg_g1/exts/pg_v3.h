#ifndef PG_V3_H
#define PG_V3_H

#include "core/object/object.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/types/pg_typedefs.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_V3 : public Object {
	GDCLASS(PG_V3, Object);
	PG_BIND;


//////////////////////////////////////////////////


public:
	static V3 &neg_x(V3 &v);
	static V3 &neg_y(V3 &v);
	static V3 &neg_z(V3 &v);


//////////////////////////////////////////////////


public:
	static V3 &set_x(V3 &v, const float x);
	static V3 &set_y(V3 &v, const float y);
	static V3 &set_z(V3 &v, const float z);


//////////////////////////////////////////////////


	static V3 set_xz_from_v2(V2 &xz, const float y);
	static V3 set_yz_from_v2(V2 &yz, const float x);
	static V3 set_zy_from_v2(V2 &zy, const float x);


//////////////////////////////////////////////////


	static V3 sum(const TA<V3> &a);
	static V3 avg(const TA<V3> &a);
	static V3 nrm(const V3 &p0, const V3 &p1, const V3 &p2);
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_V3_H
