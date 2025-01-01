#include "core/object/ref_counted.h"
#include "modules/pg_g1/core/pg_fs.h"
#include "modules/pg_g1/core/pg_msgr.h"
#include "modules/pg_g1/types/pg_types.h"
#include "modules/pg_g1/user/pg_config.h"
#include "modules/pg_g1/user/pg_input.h"
#include "modules/pg_g1/user/pg_profile.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


void PG_Config::_bind_methods() {
#ifdef PG_GD_FNS
#endif
}


Ref<PG_Config> PG_Config::mk(Ref<PG_Msgr> msgr, Ref<PG_FS> fs, Ref<PG_Profile> prf) {
	return PG_Types::mk_ref<PG_Config>(msgr, fs, prf);
}


PG_Config::PG_Config(Ref<PG_Msgr> msgr, Ref<PG_FS> fs, Ref<PG_Profile> prf) {
	_msgr = msgr;
	_fs = fs;
	_prf = prf;
	_input = PG_Input::mk(msgr, fs, prf);
	// TODO: Add other settings, graphics, audio, etc. maybe each is its own class.
}


PG_Config::~PG_Config() {}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
