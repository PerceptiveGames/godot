#include "core/object/ref_counted.h"
#include "core/templates/vmap.h"
#include "core/variant/callable.h"
#include "core/variant/variant.h"
#include "modules/pg_g1/core/pg_cmds.h"
#include "modules/pg_g1/types/pg_typedefs.h"
#include "modules/pg_g1/types/pg_types.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


// TODO: Move to e.g. player class, replace fns.
// One line for each command. Example:
// PG_Cmds::mk("god", Ref<Callable>(), Ref<Callable>())->add_dep("sv_cheats");


//////////////////////////////////////////////////
//////////////////////////////////////////////////


Ref<PG_Cmd> PG_Cmds::mk_cmd(Str id, const Callable &f_send, const Callable &f_get) {
	_commands[id] = PG_Types::mk_ref<PG_Cmd>(id, f_send, f_get);
	return _commands[id];
}


//////////////////////////////////////////////////


// TODO: Sanitize 'cmd'. Replace tabs, maybe non-ascii chars (wait, used for e.g. names?), etc.
void PG_Cmds::send(Str cmd) {
	if (cmd.is_empty()) {
		return;
	}
	PSA a = cmd.split(" ", false, 1);

	SN id = a[0];
	PSA args = a.size() > 1 ? a[1].split(" ", false) : PSA();

	if (!_commands.has(id)) {
		return;
	}

	Ref<PG_Cmd> o = _commands[id];

	o->call_send(args);
}


Vrt PG_Cmds::get(Str id) {
	return _commands[id]->call_get();
}


//////////////////////////////////////////////////


Ref<PG_Cmds> PG_Cmds::mk() {
	return PG_Types::mk_ref<PG_Cmds>();
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////


void PG_Cmd::call_send(const PSA &args) const {
	_f_send.call(args);
}


Vrt PG_Cmd::call_get() const {
	return _f_get.call();
}


//////////////////////////////////////////////////


PG_Cmd::PG_Cmd() :
	_case_sensitive(false)
	{}


PG_Cmd::PG_Cmd(Str id, const Callable &f_send, const Callable &f_get) :
	_id(id),
	_f_send(f_send),
	_f_get(f_get),
	_case_sensitive(false)
	{}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
