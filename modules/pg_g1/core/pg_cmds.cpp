#include "core/object/ref_counted.h"
#include "core/string/string_name.h"
#include "core/string/ustring.h"
#include "core/templates/vector.h"
#include "core/templates/vmap.h"
#include "core/variant/callable.h"
#include "core/variant/variant.h"
#include "modules/pg_g1/core/pg_cmds.h"
#include "modules/pg_g1/types/pg_types.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


// TODO: Move to e.g. player class, replace fns.
// One line for each command. Example:
// PG_Cmds::mk("god", Ref<Callable>(), Ref<Callable>())->add_dep("sv_cheats");


//////////////////////////////////////////////////
//////////////////////////////////////////////////


Ref<PG_Cmd> PG_Cmds::mk_cmd(String id, const Callable &f_send, const Callable &f_get) {
	_commands[id] = PG_Types::mk_ref<PG_Cmd>(id, f_send, f_get);
	return _commands[id];
}


//////////////////////////////////////////////////


// TODO: Sanitize 'cmd'. Replace tabs, maybe non-ascii chars (wait, used for e.g. names?), etc.
void PG_Cmds::send(String cmd) {
	if (cmd.is_empty()) {
		return;
	}
	Vector<String> a = cmd.split(" ", false, 1);

	StringName id = a[0];
	Vector<String> args = a.size() > 1 ? a[1].split(" ", false) : Vector<String>();

	if (!_commands.has(id)) {
		return;
	}

	Ref<PG_Cmd> o = _commands[id];

	o->call_send(args);
}


Variant PG_Cmds::receive(String id) {
	return _commands[id]->call_receive();
}


//////////////////////////////////////////////////


Ref<PG_Cmds> PG_Cmds::mk() {
	return PG_Types::mk_ref<PG_Cmds>();
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////


void PG_Cmd::call_send(const Vector<String> &args) const {
	_f_send.call(args);
}


Variant PG_Cmd::call_receive() const {
	return _f_get.call();
}


//////////////////////////////////////////////////


PG_Cmd::PG_Cmd() :
	_case_sensitive(false) {}


PG_Cmd::PG_Cmd(String id, const Callable &f_send, const Callable &f_get) :
	_id(id),
	_f_send(f_send),
	_f_get(f_get),
	_case_sensitive(false) {}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
