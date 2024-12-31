#ifndef PG_PATHS_H
#define PG_PATHS_H

#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "modules/pg_g1/core/pg_fs.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/types/pg_typedefs.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


//class PG_FS;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Paths : public RefCounted {
	GDCLASS(PG_Paths, RefCounted);
	PG_BIND;


//////////////////////////////////////////////////


protected:
	inline static Ref<PG_FS> _fs;


public:
	static void set_fs(Ref<PG_FS> fs);


//////////////////////////////////////////////////

		
public:
	static Str modules_dir_path();


//////////////////////////////////////////////////


public:
	static Str audio_ext();


//////////////////////////////////////////////////


public:
	static Str npcs_dir_path();


	static Str npc_file_path(Str file_name, Str file_ext, Vrt npc_id);


	static Str npc_dialogues_file_path(Vrt npc_id);


//////////////////////////////////////////////////


public:
	static Str file_path_with_new_ext(Str file_path, Str new_ext);


//////////////////////////////////////////////////


public:
	static Ref<PGW_Str> log_dir_path();

	static Ref<PGW_Str> log_file_path();


	static Ref<PGW_Str> old_log_file_path(Str dt);


//////////////////////////////////////////////////


public:
	static Ref<PGW_Str> input_file_path(SN profile_id);

	static Ref<PGW_Str> _gd_input_file_path(SN profile_id);


//////////////////////////////////////////////////


public:
	static Str add_ts_sfx(Str fp);
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_PATHS_H
