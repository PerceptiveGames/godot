#ifndef PG_CMDS_H
#define PG_CMDS_H

#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "core/templates/vmap.h"
#include "modules/pg_g1/data/pg_macros.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class Callable;
class String;
class StringName;
class Variant;

template <typename T>
class Vector;

template <typename K, typename V>
class VMap;

class PG_Cmd;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Cmds : public RefCounted {
	GDCLASS(PG_Cmds, RefCounted);
	PG_BIND;


//////////////////////////////////////////////////


protected:
	VMap<StringName, Ref<PG_Cmd>> _commands;


public:
	Ref<PG_Cmd> mk_cmd(String id, const Callable &f_send, const Callable &f_recv);


//////////////////////////////////////////////////


public:
	void send(String cmd);
	Variant receive(String id);


//////////////////////////////////////////////////


public:
	static Ref<PG_Cmds> mk();
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Cmd : public RefCounted {
	GDCLASS(PG_Cmd, RefCounted);
	PG_BIND;


//////////////////////////////////////////////////


	friend PG_Cmds;


//////////////////////////////////////////////////


protected:
	StringName _id;
	Vector<String> _args;
	String _title;
	String _desc;
	String _help;

	bool _case_sensitive;

	Callable _f_send;
	Callable _f_recv;


protected:
	void call_send(const Vector<String> &args) const;
	Variant call_receive() const;


//////////////////////////////////////////////////


public:
	PG_Cmd();
	PG_Cmd(String id, const Callable &f_send, const Callable &f_recv);
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_CMDS_H
