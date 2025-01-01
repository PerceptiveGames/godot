#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/sgns/pg_sgns_user.h"
#include "modules/pg_g1/types/pg_types.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


void PG_SgnsUser::_bind_methods() {
#ifdef PG_GD_FNS
	ADD_SIGNAL(MethodInfo("console_show_pressed"));
#endif
}


Ref<PG_SgnsUser> PG_SgnsUser::mk() {
	return PG_Types::mk_ref<PG_SgnsUser>();
}


PG_SgnsUser::PG_SgnsUser() {}


PG_SgnsUser::~PG_SgnsUser() {}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
