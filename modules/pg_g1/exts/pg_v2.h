#ifndef PG_V2_H
#define PG_V2_H

#include "core/object/object.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/types/pg_typedefs.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_V2 : public Object {
	GDCLASS(PG_V2, Object);
	PG_BIND;


//////////////////////////////////////////////////


public:
	static V2 &neg_x(V2 &v);
	static V2 &neg_y(V2 &v);


//////////////////////////////////////////////////


public:
	static V2 &set_x(V2 &v, const float x);
	static V2 &set_y(V2 &v, const float y);


//////////////////////////////////////////////////


public:
	static V2 set_from_v3_xy(V3 &xy);
	static V2 set_from_v3_xz(V3 &xz);
	static V2 set_from_v3_yz(V3 &yz);


//////////////////////////////////////////////////


public:
	static V2 sum(const TA<V2> &a);
	static V2 avg(const TA<V2> &a);
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_V2_H
