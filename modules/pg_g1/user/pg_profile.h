#ifndef PG_PROFILE_H
#define PG_PROFILE_H

#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/types/pg_typedefs.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class String;
class StringName;

class PG_Cheats;
class PG_Cmds;
class PG_Config;
class PG_FS;
class PG_Msgr;
class PG_Profile;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Profile : public RefCounted {
	GDCLASS(PG_Profile, RefCounted);
	PG_BIND;


//////////////////////////////////////////////////


protected:
	String _name; // DOC: Displayed name.
	StringName _id; // DOC: Folder name, snake_case and sanitized.


public:
	StringName get_id();


//////////////////////////////////////////////////


protected:
	Ref<PG_Config> _config;
	Ref<PG_Cheats> _cheats;


//////////////////////////////////////////////////


public:
	static Ref<PG_Profile> mk(Ref<PG_Msgr> msgr, Ref<PG_FS> fs, Ref<PG_Cmds> cmds);

	PG_Profile();
	PG_Profile(Ref<PG_Msgr> msgr, Ref<PG_FS> fs, Ref<PG_Cmds> cmds);
	~PG_Profile();
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_PROFILE_H
