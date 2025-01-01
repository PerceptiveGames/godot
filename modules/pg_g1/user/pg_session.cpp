#include "core/object/ref_counted.h"
#include "modules/pg_g1/core/pg_cmds.h"
#include "modules/pg_g1/core/pg_fs.h"
#include "modules/pg_g1/core/pg_msgr.h"
#include "modules/pg_g1/types/pg_types.h"
#include "modules/pg_g1/user/pg_profile.h"
#include "modules/pg_g1/user/pg_session.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


void PG_Session::mk_profile() {
	_profile = PG_Profile::mk(_msgr, _fs, _cmds);
}


//////////////////////////////////////////////////


void PG_Session::_bind_methods() {
#ifdef PG_GD_FNS
#endif
}


Ref<PG_Session> PG_Session::mk(Ref<PG_Msgr> msgr, Ref<PG_FS> fs, Ref<PG_Cmds> cmds) {
	return PG_Types::mk_ref<PG_Session>(msgr, fs, cmds);
}


PG_Session::PG_Session() {}


PG_Session::PG_Session(Ref<PG_Msgr> msgr, Ref<PG_FS> fs, Ref<PG_Cmds> cmds) {
	_msgr = msgr;
	_fs = fs;
	_cmds = cmds;
}


PG_Session::~PG_Session() {}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
