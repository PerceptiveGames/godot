#include "core/object/class_db.h"
#include "core/object/ref_counted.h"
#include "core/variant/variant.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/types/pg_pair.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


Variant PG_Pair::v1() {
	return _v1;
}


Variant PG_Pair::v2() {
	return _v2;
}


//////////////////////////////////////////////////


Ref<PG_Pair> PG_Pair::mk(const Variant &v1, const Variant &v2) {
	Ref<PG_Pair> r;
	r.instantiate(v1, v2);
	return r;
}


//////////////////////////////////////////////////


#ifdef PG_GD_FNS
void PG_Pair::_bind_methods() {
	ClassDB::bind_static_method("PG_Pair", D_METHOD("mk", "v1", "v2"), &PG_Pair::mk);
}
#endif


PG_Pair::PG_Pair() :
		_v1(),
		_v2() {}


PG_Pair::PG_Pair(const Variant &v1, const Variant &v2) :
		_v1(v1),
		_v2(v2) {}


PG_Pair::~PG_Pair() {}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
