#include "core/object/callable_method_pointer.h"
#include "core/object/ref_counted.h"
#include "core/string/ustring.h"
#include "core/templates/vector.h"
#include "core/variant/variant.h"
#include "modules/pg_g1/core/pg_cmds.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/exts/pg_num.h"
#include "modules/pg_g1/types/pg_types.h"
#include "modules/pg_g1/user/pg_cheats.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


void PG_Cheats::_god_send(Vector<String> args) {
	if (PG_Num::to_int(_cmds->receive("sv_cheats")) <= 0) {
		return;
	}
	if (args.size() > 0) {
		_god = (args[1] == "1") ? true : false;
		return;
	}
	_god = !_god;
}


Variant PG_Cheats::_god_recv() const {
	return _god;
}


//////////////////////////////////////////////////


Ref<PG_Cheats> PG_Cheats::mk(Ref<PG_Cmds> cmds) {
	return PG_Types::mk_ref<PG_Cheats>(cmds);
}


PG_Cheats::PG_Cheats() :
	_god(false) {}


PG_Cheats::PG_Cheats(Ref<PG_Cmds> cmds) {
	_cmds = cmds;
	_cmds->mk_cmd("god", callable_mp(this, &PG_Cheats::_god_send), callable_mp(this, &PG_Cheats::_god_recv));
}


PG_Cheats::~PG_Cheats() {}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
