#ifndef PG_PATHS_H
#define PG_PATHS_H

#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/types/pgw.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class String;
class StringName;
class Variant;

class PG_FS;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Paths : public RefCounted {
	GDCLASS(PG_Paths, RefCounted);
	PG_BIND;


//////////////////////////////////////////////////


protected:
	static Ref<PG_FS> _fs;


public:
	static void set_fs(Ref<PG_FS> fs);


//////////////////////////////////////////////////

		
public:
	static String modules_dir_path();


//////////////////////////////////////////////////


public:
	static String audio_ext();


//////////////////////////////////////////////////


public:
	static String npcs_dir_path();

	static String npc_file_path(String file_name, String file_ext, Variant npc_id);

	static String npc_dialogues_file_path(Variant npc_id);


//////////////////////////////////////////////////


public:
	static String file_path_with_new_ext(String file_path, String new_ext);


//////////////////////////////////////////////////


public:
	static Ref<PGW_Str> log_dir_path();

	static Ref<PGW_Str> log_file_path();

	static Ref<PGW_Str> old_log_file_path(String dt);


//////////////////////////////////////////////////


public:
	static Ref<PGW_Str> input_file_path(StringName profile_id);

	static Ref<PGW_Str> _gd_input_file_path(StringName profile_id);


//////////////////////////////////////////////////


public:
	static String add_ts_sfx(String fp);
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_PATHS_H
