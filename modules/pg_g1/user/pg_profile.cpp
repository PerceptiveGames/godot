#include "core/object/ref_counted.h"
#include "modules/pg_g1/core/pg_cmds.h"
#include "modules/pg_g1/core/pg_fs.h"
#include "modules/pg_g1/core/pg_msgr.h"
#include "modules/pg_g1/types/pg_typedefs.h"
#include "modules/pg_g1/types/pg_types.h"
#include "modules/pg_g1/user/pg_cheats.h"
#include "modules/pg_g1/user/pg_config.h"
#include "modules/pg_g1/user/pg_profile.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


SN PG_Profile::get_id() {
	return _id;
}


//////////////////////////////////////////////////


#ifdef PG_GD_FNS
void PG_Profile::_bind_methods() {
}
#endif


Ref<PG_Profile> PG_Profile::mk(Ref<PG_Msgr> msgr, Ref<PG_FS> fs, Ref<PG_Cmds> cmds) {
	return PG_Types::mk_ref<PG_Profile>(msgr, fs, cmds);
}


PG_Profile::PG_Profile() {}


PG_Profile::PG_Profile(Ref<PG_Msgr> msgr, Ref<PG_FS> fs, Ref<PG_Cmds> cmds) {
	_config = PG_Config::mk(msgr, fs, this);
	_cheats = PG_Cheats::mk(cmds);
}


PG_Profile::~PG_Profile() {}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
