#ifndef PG_SESSION_H
#define PG_SESSION_H

#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "modules/pg_g1/data/pg_macros.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


// TODO: Create a "__default__" profile loaded at game start
// that handles the profile selection screen
// and the basic accessibility settings.


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class String;

class PG_Cmds;
class PG_FS;
class PG_Msgr;
class PG_Profile;
class PG_Session;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Session : public RefCounted {
	GDCLASS(PG_Session, RefCounted);
	PG_BIND;


//////////////////////////////////////////////////


	template <typename T>
	friend class Ref;


//////////////////////////////////////////////////


protected:
	Ref<PG_FS> _fs;
	Ref<PG_Msgr> _msgr;
	Ref<PG_Cmds> _cmds;


//////////////////////////////////////////////////


protected:
	Ref<PG_Profile> _profile;


public:
	void mk_profile(String id);


//////////////////////////////////////////////////


public:
	static Ref<PG_Session> mk(Ref<PG_Msgr> msgr, Ref<PG_FS> fs, Ref<PG_Cmds> cmds);


protected:
	PG_Session();
	PG_Session(Ref<PG_Msgr> msgr, Ref<PG_FS> fs, Ref<PG_Cmds> cmds);


public:
	~PG_Session();
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_SESSION_H
