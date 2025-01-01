#ifndef PG_MSGR_H
#define PG_MSGR_H

#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "core/templates/vmap.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/types/pg_typedefs.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


// TODO: Every console command should be a class instance,
// with props and getter + optional setter
// and two level requirements (e.g. sv_cheats) to be get or set.
// Maybe write those classes at relevant location each time.
// TODO: Make friend classes instead of everything public.
// TODO: Maybe turn 'TypedArray<String> strs' arg type into 'Vector<String>'.


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class Callable;
enum Error : int;
class String;
class StringName;

template <typename T>
class TypedArray;

template <typename T>
class Vector;

template <typename K, typename V>
class VMap;

class PG_Msg;
class PG_MsgrTgt;


//////////////////////////////////////////////////


enum PGE_MsgLevel {
	NONE = 0,
	INPUT = 1,
	INFO = 2,
	WARNING = 3,
	ERROR = 4,
	INPUT_VIP = 5,
	INFO_VIP = 6,
	WARNING_VIP = 7,
	FATAL = 8,
};

String PGE_MsgLevelStr(PGE_MsgLevel lvl);


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Msgs : public RefCounted {
	GDCLASS(PG_Msgs, RefCounted);


//////////////////////////////////////////////////


protected:
	VMap<StringName, String> _m;


public:
	String get(StringName k) const;


//////////////////////////////////////////////////


public:
	static Ref<PG_Msgs> mk();

	PG_Msgs();
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Msgr : public RefCounted {
	GDCLASS(PG_Msgr, RefCounted);
	PG_BIND;


//////////////////////////////////////////////////


protected:
	Ref<PG_Msgs> _msgs;

	VMap<StringName, Ref<PG_MsgrTgt>> _tgts;


//////////////////////////////////////////////////

	
public:
	Ref<PG_MsgrTgt> mk_tgt(StringName id, const Callable &f, int min_lvl, int max_lvl, bool is_enabled);


//////////////////////////////////////////////////


public:
	Ref<PG_Msg> mk_msg(PGE_MsgLevel lvl, String tgt, StringName id, String txt, Error e);
	Ref<PG_Msg> mk_msg(PGE_MsgLevel lvl, Vector<StringName> tgts, StringName id, String txt, Error e);


//////////////////////////////////////////////////


public:
	Ref<PG_Msg> build(PGE_MsgLevel lvl, Vector<StringName> tgts, StringName id, Error e, TypedArray<String> strs);

	Ref<PG_Msg> bcast(Ref<PG_Msg> msg);
	Ref<PG_Msg> bcast(PGE_MsgLevel lvl, StringName id);
	Ref<PG_Msg> bcast(PGE_MsgLevel lvl, StringName id, String str);
	Ref<PG_Msg> bcast(PGE_MsgLevel lvl, StringName id, Error e, String str);
	Ref<PG_Msg> bcast(PGE_MsgLevel lvl, String tgt, StringName id, Error e, String str);
	Ref<PG_Msg> bcast(PGE_MsgLevel lvl, Vector<StringName> tgts, StringName id, Error e, String str);

	Ref<PG_Msg> bcast(PGE_MsgLevel lvl, StringName id, TypedArray<String> strs);
	Ref<PG_Msg> bcast(PGE_MsgLevel lvl, StringName id, Error e, TypedArray<String> strs);
	Ref<PG_Msg> bcast(PGE_MsgLevel lvl, String tgt, StringName id, Error e, TypedArray<String> strs);
	Ref<PG_Msg> bcast(PGE_MsgLevel lvl, Vector<StringName> tgts, StringName id, Error e, TypedArray<String> strs);

#ifdef PG_GD_FNS
	Ref<PG_Msg> _gd_bcast(PGE_MsgLevel lvl, Vector<StringName> tgts, StringName id, Error e, TypedArray<String> strs);
#endif


//////////////////////////////////////////////////


public:
	static Ref<PG_Msgr> mk();

	PG_Msgr();
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_MsgrTgt : public RefCounted {
	GDCLASS(PG_MsgrTgt, RefCounted);


//////////////////////////////////////////////////


protected:
	StringName _id;

	Callable _f;

	int _min_lvl;
	int _max_lvl;

	bool _is_enabled;


//////////////////////////////////////////////////


public:
	void set_enabled(bool v);


//////////////////////////////////////////////////


public:
	void send(Ref<PG_Msg> msg);


//////////////////////////////////////////////////


public:
	static Ref<PG_MsgrTgt> mk(StringName id, const Callable &f, int min_lvl, int max_lvl, bool is_enabled);

	PG_MsgrTgt();
	PG_MsgrTgt(StringName id, const Callable &f, int min_lvl, int max_lvl, bool is_enabled);
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Msg : public RefCounted {
	GDCLASS(PG_Msg, RefCounted);


//////////////////////////////////////////////////


public:
	StringName id;
	PGE_MsgLevel lvl;
	String txt;
	Error e;
	Vector<String> st;
	Vector<StringName> tgts;


//////////////////////////////////////////////////


public:
	PG_Msg();
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_MSGR_H
