#ifndef PG_CMDS_H
#define PG_CMDS_H

#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "core/templates/vmap.h"
#include "modules/pg_g1/types/pg_typedefs.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Cmd;

class Callable;

template <typename K, typename V>
class VMap;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Cmds : public RefCounted {
	GDCLASS(PG_Cmds, RefCounted);


//////////////////////////////////////////////////


protected:
	VMap<SN, Ref<PG_Cmd>> _commands;


public:
	Ref<PG_Cmd> mk_cmd(Str id, const Callable &f_send, const Callable &f_get);


//////////////////////////////////////////////////


public:
	void send(Str cmd);

	// TODO: Rename to avoid clash?
	Vrt get(Str id);


//////////////////////////////////////////////////


public:
	static Ref<PG_Cmds> mk();
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Cmd : public RefCounted {
	GDCLASS(PG_Cmd, RefCounted);


//////////////////////////////////////////////////


protected:
	SN _id;
	Vec<Str> _args;
	Str _title;
	Str _desc;
	Str _help;

	bool _case_sensitive;

	Callable _f_send;
	Callable _f_get;


public:
	void call_send(const PSA &args) const;


	Vrt call_get() const;


//////////////////////////////////////////////////


public:
	PG_Cmd();

	PG_Cmd(Str id, const Callable &f_send, const Callable &f_get);
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_CMDS_H
