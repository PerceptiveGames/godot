#include "core/object/callable_method_pointer.h"
#include "core/object/ref_counted.h"
#include "modules/pg_g1/core/pg_cmds.h"
#include "modules/pg_g1/exts/pg_num.h"
#include "modules/pg_g1/types/pg_typedefs.h"
#include "modules/pg_g1/types/pg_types.h"
#include "modules/pg_g1/user/pg_cheats.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


void PG_Cheats::_god_send(PSA args) {
	if (PG_Num::to_int(_cmds->get("sv_cheats")) <= 0) {
		return;
	}
	if (args.size() > 0) {
		_god = (args[1] == "1") ? true : false;
		return;
	}
	_god = !_god;
}


Vrt PG_Cheats::_god_get() const {
	return _god;
}


//////////////////////////////////////////////////


#ifdef PG_GD_FNS
void PG_Cheats::_bind_methods() {
}
#endif


Ref<PG_Cheats> PG_Cheats::mk(Ref<PG_Cmds> cmds) {
	return PG_Types::mk_ref<PG_Cheats>(cmds);
}


PG_Cheats::PG_Cheats(Ref<PG_Cmds> cmds) {
	_cmds = cmds;
	_cmds->mk_cmd("god", callable_mp(this, &PG_Cheats::_god_send), callable_mp(this, &PG_Cheats::_god_get));
}


PG_Cheats::~PG_Cheats() {
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
