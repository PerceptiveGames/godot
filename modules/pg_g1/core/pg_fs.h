#ifndef PG_FS_H
#define PG_FS_H

#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "core/templates/vmap.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/types/pgw.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class Callable;
class FileAccess;
class PackedScene;
class Script;
class String;

template <typename T>
class Vector;

template <typename K, typename V>
class VMap;

class PG_FileLogger;
class PG_FS;
class PG_Msg;
class PG_Msgr;
class PG_MsgrTgt;
class PG_Timer;
class PG_Timers;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_FS : public RefCounted {
	GDCLASS(PG_FS, RefCounted);
	PG_BIND;


//////////////////////////////////////////////////


protected:
	Ref<PG_Msgr> _msgr;
	Ref<PG_Timers> _timers;


//////////////////////////////////////////////////


protected:
	VMap<String, Ref<FileAccess>> _open_files;
	VMap<String, int> _last_opened_times;
	VMap<String, int> _last_closed_times;
	//VMap<String, bool> _last_op; // DOC: -1: none, 0: close, 1: open.
	VMap<String, Ref<PG_Timer>> _open_files_timers;

	Ref<PG_FileLogger> file_logger;


public:
	Ref<FileAccess> open_file(String path, bool create_if_none = true, bool auto_close_shortly = true, bool truncate = false);
	void close_file(String path);
	bool create_file_if_none(String path);


//////////////////////////////////////////////////


public:
	Ref<PGW_Str> mk_dir(String path);


//////////////////////////////////////////////////


public:
	// TODO: Maybe add bool arg for putting into recycle bin.
	bool rn_or_rm(String fp, String nn);


//////////////////////////////////////////////////


public:
	Ref<PGW_Dict> get_md_dt(String fp, bool cur_tm_if_none);
	Ref<PGW_Str> get_fmt_md_dt(String fp, bool cur_tm_if_none);


//////////////////////////////////////////////////


public:
	// DOC: sort_f takes a reference to the array 'arr'.
	bool get_file_paths(Vector<String> &arr, String root_dir_path, String rel_dir_path, const Callable &filter_f, bool recursive, bool abs_paths, bool sort, const Callable &sort_f = nullptr);


//////////////////////////////////////////////////


public:
	Ref<PackedScene> load_packed_scene(String path);
	Ref<Script> load_script(String path);


//////////////////////////////////////////////////


public:
	static Ref<PG_FS> mk(Ref<PG_Msgr> msgr, Ref<PG_Timers> timers);

	PG_FS();
	PG_FS(Ref<PG_Msgr> msgr, Ref<PG_Timers> timers);
	~PG_FS();
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_FileLogger : public RefCounted {
	GDCLASS(PG_FileLogger, RefCounted);


//////////////////////////////////////////////////


protected:
	Ref<PG_FS> _fs;
	Ref<PG_Msgr> _msgr;
	Ref<PG_MsgrTgt> _tgt;


//////////////////////////////////////////////////


protected:
	PG_INLINE bool _old_logs_fn_filter(String f);

	void _delete_old_logs();

	void _write(Ref<PG_Msg> msg);


//////////////////////////////////////////////////


public:
	static Ref<PG_FileLogger> mk(Ref<PG_Msgr> msgr, Ref<PG_FS> fs);

	PG_FileLogger(Ref<PG_Msgr> msgr, Ref<PG_FS> fs);
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_FS_H
