#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/signals/pg_signals_user.h"
#include "modules/pg_g1/types/pg_types.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


void PG_SignalsUser::_bind_methods() {
#ifdef PG_GD_FNS
	ADD_SIGNAL(MethodInfo("console_show_pressed"));
#endif
}


Ref<PG_SignalsUser> PG_SignalsUser::mk() {
	return PG_Types::mk_ref<PG_SignalsUser>();
}


PG_SignalsUser::PG_SignalsUser() {}


PG_SignalsUser::~PG_SignalsUser() {}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
