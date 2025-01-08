#include "core/object/ref_counted.h"
#include "core/os/os.h"
#include "core/os/time.h"
#include "core/string/string_name.h"
#include "core/string/ustring.h"
#include "core/variant/dictionary.h"
#include "core/variant/variant.h"
#include "modules/pg_g1/core/pg_fs.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/data/pg_paths.h"
#include "modules/pg_g1/types/pgw.h"
#include <cstdint>



//////////////////////////////////////////////////
//////////////////////////////////////////////////


Ref<PG_FS> PG_Paths::_fs;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


void PG_Paths::set_fs(Ref<PG_FS> fs) {
	_fs = fs;
}


//////////////////////////////////////////////////


String PG_Paths::modules_dir_path() {
	return "X:\\pg_godot_v1\\godot\\modules\\";
}


//////////////////////////////////////////////////


String PG_Paths::audio_ext() {
	return "wav";
}


//////////////////////////////////////////////////


String PG_Paths::npcs_dir_path() {
	return "res://pgg1/characters/npcs/";
}


String PG_Paths::npc_file_path(String file_name, String file_ext, Variant npc_id) {
	return vformat("{%s}{%s}/{%s}_{%s}.{%s}", npcs_dir_path(), String(npc_id), file_name, String(npc_id), file_ext);
}


String PG_Paths::npc_dialogues_file_path(Variant npc_id) {
	return npc_file_path("pgc_npc_dialogue", "gd", String(npc_id));
}


//////////////////////////////////////////////////


String PG_Paths::file_path_with_new_ext(String file_path, String new_ext) {
	return vformat("%s.%s", file_path.get_basename(), new_ext);
}


//////////////////////////////////////////////////


Ref<PGW_Str> PG_Paths::log_dir_path() {
	_return_st_(_fs->mk_dir("user://logs/"));
}

Ref<PGW_Str> PG_Paths::log_file_path() {
	_return_st_(_fs->mk_dir("user://logs/output.log"));
}

Ref<PGW_Str> PG_Paths::old_log_file_path(String dt) {
	_return_st_(_fs->mk_dir(vformat("user://logs/output_%s.log", dt)));
}


//////////////////////////////////////////////////


Ref<PGW_Str> PG_Paths::input_file_path(StringName profile_id) {
	_return_st_(_fs->mk_dir(vformat("user://profiles/%s/input.cfg", profile_id)));
}

Ref<PGW_Str> PG_Paths::_gd_input_file_path(StringName profile_id) {
	_return_st_(input_file_path(profile_id));
}


//////////////////////////////////////////////////


// DOC: Assumes the file has an extension.
String PG_Paths::add_ts_sfx(String fp) {
	int dt = int(PG_S(OS)->get_unix_time());
	int tz_ofs = PG_S(OS)->get_time_zone_info().bias * 60;
	// DOC: Cast is to avoid "A sub-expression may overflow before being assigned to a wider type" warning.
	Dictionary d = PG_S(Time)->get_date_dict_from_unix_time(static_cast<int64_t>(dt) + tz_ofs);
	return vformat("%s_%04d-%02d-%02d_%02dh%02dm%02ds.%s", fp.get_basename(), d["year"], d["month"], d["day"], d["hour"], d["minute"], d["second"], fp.get_extension());
}


//////////////////////////////////////////////////


void PG_Paths::_bind_methods() {
#ifdef PG_GD_FNS
	//ClassDB::bind_static_method("PG_Paths", D_METHOD("input_file_path", "profile_id"), &PG_Paths::_gd_input_file_path);
#endif
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
