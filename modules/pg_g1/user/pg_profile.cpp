#include "core/object/class_db.h"
#include "core/object/ref_counted.h"
#include "core/string/string_name.h"
#include "core/string/ustring.h"
#include "modules/pg_g1/core/pg_cmds.h"
#include "modules/pg_g1/core/pg_fs.h"
#include "modules/pg_g1/core/pg_msgr.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/types/pg_types.h"
#include "modules/pg_g1/user/pg_cheats.h"
#include "modules/pg_g1/user/pg_config.h"
#include "modules/pg_g1/user/pg_profile.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


StringName PG_Profile::get_id() {
	return _id;
}


bool PG_Profile::is_transient() const {
	return _transient;
}


//////////////////////////////////////////////////


void PG_Profile::_bind_methods() {
#ifdef PG_GD_FNS
	ClassDB::bind_method(D_METHOD("get_id"), &PG_Profile::get_id);
	ClassDB::bind_method(D_METHOD("is_transient"), &PG_Profile::is_transient);
#endif
}


Ref<PG_Profile> PG_Profile::mk(Ref<PG_Msgr> msgr, Ref<PG_FS> fs, Ref<PG_Cmds> cmds, String prf_id) {
	return PG_Types::mk_ref<PG_Profile>(msgr, fs, cmds, prf_id);
}

Ref<PG_Profile> PG_Profile::mk_transient(Ref<PG_Msgr> msgr, Ref<PG_FS> fs, Ref<PG_Cmds> cmds) {
	return PG_Types::mk_ref<PG_Profile>(msgr, fs, cmds);
}


PG_Profile::PG_Profile() :
		_transient(true) {}


PG_Profile::PG_Profile(Ref<PG_Msgr> msgr, Ref<PG_FS> fs, Ref<PG_Cmds> cmds, String prf_id) {
	_transient = prf_id.is_empty();

	_id = prf_id;
	_config = PG_Config::mk(msgr, fs, this);
	_cheats = PG_Cheats::mk(cmds);
}


PG_Profile::~PG_Profile() {}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
