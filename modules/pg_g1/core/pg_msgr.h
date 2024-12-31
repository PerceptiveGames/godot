#ifndef PG_MSGR_H
#define PG_MSGR_H

//#include "core/error/error_list.h"
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
// TODO: Maybe turn 'TA<Str> strs' arg type into 'Vec<Str>'.


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Msg;
class PG_MsgrTgt;

class Callable;
enum Error : int;


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


Str PGE_MsgLevelStr(PGE_MsgLevel lvl);


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Msgs : public RefCounted {
	GDCLASS(PG_Msgs, RefCounted);


//////////////////////////////////////////////////


protected:
	VMap<SN, Str> _m;


public:
	Str get(SN k) const;


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

	VMap<SN, Ref<PG_MsgrTgt>> _tgts;


//////////////////////////////////////////////////

	
public:
	Ref<PG_MsgrTgt> mk_tgt(SN id, const Callable &f, int min_lvl, int max_lvl, bool is_enabled);


//////////////////////////////////////////////////


public:
	Ref<PG_Msg> mk_msg(PGE_MsgLevel lvl, Str tgt, SN id, Str txt, Error e);

	Ref<PG_Msg> mk_msg(PGE_MsgLevel lvl, SNV tgts, SN id, Str txt, Error e);


//////////////////////////////////////////////////


public:
	Ref<PG_Msg> build(PGE_MsgLevel lvl, SNV tgts, SN id, Error e, TA<Str> strs);


	Ref<PG_Msg> bcast(Ref<PG_Msg> msg);


	Ref<PG_Msg> bcast(PGE_MsgLevel lvl, SN id);

	Ref<PG_Msg> bcast(PGE_MsgLevel lvl, SN id, Str str);

	Ref<PG_Msg> bcast(PGE_MsgLevel lvl, SN id, Error e, Str str);

	Ref<PG_Msg> bcast(PGE_MsgLevel lvl, Str tgt, SN id, Error e, Str str);

	Ref<PG_Msg> bcast(PGE_MsgLevel lvl, SNV tgts, SN id, Error e, Str str);


	Ref<PG_Msg> bcast(PGE_MsgLevel lvl, SN id, TA<Str> strs);

	Ref<PG_Msg> bcast(PGE_MsgLevel lvl, SN id, Error e, TA<Str> strs);

	Ref<PG_Msg> bcast(PGE_MsgLevel lvl, Str tgt, SN id, Error e, TA<Str> strs);

	Ref<PG_Msg> bcast(PGE_MsgLevel lvl, SNV tgts, SN id, Error e, TA<Str> strs);


#ifdef PG_GD_FNS
	Ref<PG_Msg> _gd_bcast(PGE_MsgLevel lvl, SNV tgts, SN id, Error e, TA<Str> strs);
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
	SN _id;

	Callable _f;

	int _min_lvl, _max_lvl;

	bool _is_enabled;


//////////////////////////////////////////////////


public:
	void set_enabled(bool v);


//////////////////////////////////////////////////


public:
	void send(Ref<PG_Msg> msg);


//////////////////////////////////////////////////


public:
	static Ref<PG_MsgrTgt> mk(SN id, const Callable &f, int min_lvl, int max_lvl, bool is_enabled);


	PG_MsgrTgt();


	PG_MsgrTgt(SN id, const Callable &f, int min_lvl, int max_lvl, bool is_enabled);
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Msg : public RefCounted {
	GDCLASS(PG_Msg, RefCounted);


//////////////////////////////////////////////////


public:
	SN id;
	PGE_MsgLevel lvl;
	Str txt;
	Error e;
	PSA st;
	SNV tgts;


//////////////////////////////////////////////////


public:
	PG_Msg();
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_MSGR_H
