#include "core/error/error_list.h"
#include "core/io/dir_access.h"
#include "core/io/file_access.h"
#include "core/io/resource_loader.h"
#include "core/object/callable_method_pointer.h"
#include "core/object/ref_counted.h"
#include "core/object/script_language.h"
#include "core/os/os.h"
#include "core/os/time.h"
#include "core/string/ustring.h"
#include "core/templates/vector.h"
#include "core/templates/vmap.h"
#include "core/variant/callable.h"
#include "core/variant/dictionary.h"
#include "core/variant/variant.h"
#include "modules/pg_g1/core/pg_fs.h"
#include "modules/pg_g1/core/pg_msgr.h"
#include "modules/pg_g1/core/pg_timers.h"
#include "modules/pg_g1/data/pg_const.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/data/pg_paths.h"
#include "modules/pg_g1/exts/pg_arr.h"
#include "modules/pg_g1/exts/pg_rgx.h"
#include "modules/pg_g1/types/pg_typedefs.h"
#include "modules/pg_g1/types/pg_types.h"
#include "modules/pg_g1/types/pgw.h"
#include "scene/resources/packed_scene.h"
#include <cstdint>


//////////////////////////////////////////////////
//////////////////////////////////////////////////


// TODO: Avoid unbind()/bind() in Callables, because it creates a new Callable.


//////////////////////////////////////////////////
//////////////////////////////////////////////////


Ref<FileAccess> PG_FS::open_file(String path, bool create_if_none, bool auto_close_shortly, bool truncate) {
	Ref<FileAccess> file;
	if (_open_files.has(path)) {
		file = _open_files[path];
		if (!file.is_valid() || !file->is_open()) {
			//file = nullptr;
			//_open_files[path] = nullptr;
			_open_files.erase(path);
		}
	}
	if (!file.is_valid() || !file->is_open()) {
		String id;
		Error e;
		if (!FileAccess::exists(path)) {
			if (create_if_none) {
				_if_st_(mk_dir(path)->nok()) {
					// TODO: Correct?
					return PG_Types::unref(file);
				}
				// DOC: Creates new file.
				file = FileAccess::open(path, FileAccess::WRITE_READ, &e);
				id = "MK_FILE";
			}
		} else {
			if (truncate) {
				// DOC: Truncates existing file.
				file = FileAccess::open(path, FileAccess::WRITE_READ, &e);
				id = "TRUNC_FILE";
			} else {
				// DOC: Appends to existing file.
				file = FileAccess::open(path, FileAccess::READ_WRITE, &e);
				file->seek_end();
				id = "OPEN_FILE";
			}
		}
		if (!file.is_valid()) {
			_st_(_msgr->bcast(PGE_MsgLevel::ERROR, id, e, path));
			// TODO: Correct?
			return PG_Types::unref(file);
		}
		_open_files[path] = file;
	}
	if (auto_close_shortly) {
		Ref<PG_Timer> timer;
		// TODO: Deal with the return values from restart() and start().
		if (_open_files_timers.has(path)) {
			timer = _open_files_timers[path];
			_st_(timer->restart());
		} else {
			timer = _timers->simple(nullptr, pg_file_auto_close_delay, callable_mp(this, &PG_FS::close_file).unbind(1).bind(path));
			_st_(timer->start());
		}
	}
	return nullptr;
}


// DOC: Flushes and closes the file.
void PG_FS::close_file(String path) {
	if (_open_files.has(path)) {
		Ref<FileAccess> file = _open_files[path];
		_open_files.erase(path);
		_open_files_timers.erase(path);
		if (file.is_valid()) {
			// TODO: Check if there is a way to detect that a file cannot be closed, and return error if so.
			file->close();
		} else {
			_st_(_msgr->bcast(PGE_MsgLevel::WARNING, "CLOSE_FILE_IMPROPER", path));
		}
	} else {
		//return PGV_Str::e("CLOSE_FILE_ALREADY_CLOSED", path);
	}
}


// DOC: Returns true if file either already exists, or has successfully been created.
// DOC: Used e.g. to generate empty config files.
bool PG_FS::create_file_if_none(String path) {
	_st_(Ref<FileAccess> f = open_file(path, true, false));
	if (f.is_valid()) {
		_st_(close_file(path));
		return true;
	}
	return false;
}


//////////////////////////////////////////////////


Ref<PGW_Str> PG_FS::mk_dir(String path) {
	String r = path;
	if (!r.get_extension().is_empty()) {
		r = r.get_base_dir();
	}
	if (DirAccess::exists(r)) {
		_return_st_(PGW_Str::mk_r(path));
	}
	if (Error e = DirAccess::make_dir_recursive_absolute(r)) {
		_st_(_msgr->bcast(PGE_MsgLevel::ERROR, "MK_DIR", e, r));
		return PGW_Str::mk_nok();
		//_return_st_(PGW_Str::mk_e(PGE_MsgLevel::ERROR, "MK_DIR", e, r)->bcast());
	}
	_return_st_(PGW_Str::mk_r(path));
}


//////////////////////////////////////////////////


bool PG_FS::rn_or_rm(String fp, String nn) {
	if (_open_files.has(fp)) {
		_st_(_msgr->bcast(PGE_MsgLevel::ERROR, "RN_FILE_OPEN", PG_Arr::mk_ta_str(fp, nn)));
		return false;
	}
	if (Error e = DirAccess::rename_absolute(fp, nn)) {
		_st_(_msgr->bcast(PGE_MsgLevel::ERROR, "RN_OR_TRASH_FILE", e, PG_Arr::mk_ta_str(fp, nn)));
		// DOC: move_to_trash() only returns a generic Error::FAILED, so no need to retrieve error to display it in error message.
		if (e = PG_S(OS)->move_to_trash(fp)) {
			_st_(_msgr->bcast(PGE_MsgLevel::ERROR, "TRASH_OR_RM_FILE", fp));
			if (e = DirAccess::remove_absolute(fp)) {
				_st_(_msgr->bcast(PGE_MsgLevel::ERROR, "RM_FILE", e, fp));
				return false;
			} else {
				_st_(_msgr->bcast(PGE_MsgLevel::INFO_VIP, "RM_FILE_OK", fp));
			}
		} else {
			_st_(_msgr->bcast(PGE_MsgLevel::INFO_VIP, "TRASH_FILE_OK", fp));
		}
	}
	return true;
}


//////////////////////////////////////////////////


// DOC: Fallback is current time if modified date cannot be retrieved and 'cur_tm_if_none' is true.
Ref<PGW_Dict> PG_FS::get_md_dt(String fp, bool cur_tm_if_none) {
	if (!FileAccess::exists(fp)) {
		_st_(_msgr->bcast(PGE_MsgLevel::ERROR, "FILE_NOT_EXIST", fp));
		return PGW_Dict::mk_nok();
	}
	// DOC: There is no public non-static method to get modified time, so there is no point
	// in creating a FileAccess instance manually to be used for both checking file existence
	// and modified time.
	int md_dt = FileAccess::get_modified_time(fp);
	if (md_dt == 0) {
		if (cur_tm_if_none) {
			md_dt = int(PG_S(OS)->get_unix_time());
		} else {
			_st_(_msgr->bcast(PGE_MsgLevel::ERROR, "FILE_MD_DT", fp));
			return PGW_Dict::mk_nok();
		}
	}
	int tz_ofs = PG_S(OS)->get_time_zone_info().bias * 60;
	// DOC: Cast is to avoid "A sub-expression may overflow before being assigned to a wider type" warning.
	Dictionary d = PG_S(Time)->get_date_dict_from_unix_time(static_cast<int64_t>(md_dt) + tz_ofs);

	return PGW_Dict::mk_r(d);
}


Ref<PGW_Str> PG_FS::get_fmt_md_dt(String fp, bool cur_tm_if_none) {
	_st_(Ref<PGW_Dict> rf = get_md_dt(fp, cur_tm_if_none));
	if (rf->nok()) {
		return PGW_Str::mk_nok();
	}
	Dictionary d = rf->r();
	return PGW_Str::mk_r(vformat("%04d-%02d-%02d_%02dh%02dm%02ds", d["year"], d["month"], d["day"], d["hour"], d["minute"], d["second"]));
}


//////////////////////////////////////////////////


bool PG_FS::get_file_paths(Vector<String> &arr, String root_dir_path, String rel_dir_path, const Callable &filter_f, bool recursive, bool abs_paths, bool sort, const Callable &sort_f) {
	String abs_dir_path = root_dir_path.path_join(rel_dir_path);
	Error e = Error::OK;
	Ref<DirAccess> dir = DirAccess::open(abs_dir_path, &e);
	if (dir.is_null()) {
		_st_(_msgr->bcast(PGE_MsgLevel::ERROR, "OPEN_DIR", e, abs_dir_path));
		return false;
	}
	dir->set_include_navigational(false);
	if (Error e = dir->list_dir_begin()) {
		_st_(_msgr->bcast(PGE_MsgLevel::ERROR, "RD_DIR", e, abs_dir_path));
		return false;
	}
	String file_name = dir->get_next();
	while (file_name != "") {
		String rel_file_path = rel_dir_path.path_join(file_name);
		if (dir->current_is_dir()) {
			if (recursive) {
				_if_st_(!get_file_paths(arr, root_dir_path, rel_file_path, filter_f, true, abs_paths, sort, sort_f)) {
					return false;
				}
			}
		} else {
			String file_path = abs_paths ? abs_dir_path.path_join(file_name) : rel_file_path;
			if (filter_f.call(file_path)) {
				arr.append(file_path);
			}
		}
		file_name = dir->get_next();
	}
	// DOC: Only executes sort_f at the end of the first iteration (i.e. at the end of execution).
	if (sort) {
		if (sort_f != nullptr && sort_f.is_valid()) {
			arr.sort_custom<CallableComparator, true>(sort_f);
		} else {
			arr.sort();
		}
	}
	return true;
}


//////////////////////////////////////////////////


Ref<PackedScene> PG_FS::load_packed_scene(String path) {
	return cast_to<PackedScene>(*ResourceLoader::load(path));
}


Ref<Script> PG_FS::load_script(String path) {
	return cast_to<Script>(*ResourceLoader::load(path, "Script"));
}


//////////////////////////////////////////////////


void PG_FS::_bind_methods() {
#ifdef PG_GD_FNS
#endif
}


Ref<PG_FS> PG_FS::mk(Ref<PG_Msgr> msgr, Ref<PG_Timers> timers) {
	return PG_Types::mk_ref<PG_FS>(msgr, timers);
}


PG_FS::PG_FS() {}


PG_FS::PG_FS(Ref<PG_Msgr> msgr, Ref<PG_Timers> timers) {
	_msgr = msgr;
	_timers = timers;

	//DOC: First thing to do, this needs to be called early.
	file_logger = PG_FileLogger::mk(msgr, this);
}


PG_FS::~PG_FS() {
	for (int i = 0; i < _open_files.size(); ++i) {
		_st_(close_file(_open_files.getk(i)));
	}
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////


// DOC: 'fn': file name
bool PG_FileLogger::_old_logs_fn_filter(String st) {
	return PG_Rgx::has("old_log_fmt", st);
}


void PG_FileLogger::_delete_old_logs() {
	_st_(Ref<PGW_Str> d = PG_Paths::log_dir_path());
	Vector<String> arr;
	_if_st_(d->ok() && _fs->get_file_paths(arr, d->r(), "", callable_mp(this, &PG_FileLogger::_old_logs_fn_filter), false, true, true)) {
		for (int i = 0; i < arr.size() - pg_max_log_files; ++i) {
			if (Error e = DirAccess::remove_absolute(arr[i])) {
				_st_(_msgr->bcast(PGE_MsgLevel::WARNING, "RM_FILE", e, arr[i]));
			}
		}
	}
}


// TODO: trim_prefix
void PG_FileLogger::_write(Ref<PG_Msg> msg) {
	_st_(Ref<PGW_Str> fp = PG_Paths::log_file_path());
	if (!fp->ok()) {
		// TODO: Bcast error everywhere but file.
		return;
	}
	_st_(Ref<FileAccess> f = _fs->open_file(fp->r()));
	if (!f.is_valid()) {
		// TODO: Bcast error everywhere but file.
		return;
	}
	String t = uitos(Time::get_singleton()->get_ticks_usec());
	String pfx = vformat("%s: %s:", t.lpad(9, "0").insert(6, "."), PGE_MsgLevelStr(msg->lvl)).rpad(50);
	// TODO: For other types that use bbcode.
	// https://docs.godotengine.org/en/latest/tutorials/ui/bbcode_in_richtextlabel.html
	//String c = trn_eq(msg->lvl, PGE_MsgLevel::WARNING, "yellow", PGE_MsgLevel::ERROR, "red", PGE_MsgLevel::FATAL, "red", "white");
	//String s = vformat("[color=aquamarine]%s[/color][color=%s]%s[/color]", pfx, c, msg->txt);
	//f->store_string(s);
	f->store_string(pfx + msg->txt);
}


//////////////////////////////////////////////////


Ref<PG_FileLogger> PG_FileLogger::mk(Ref<PG_Msgr> msgr, Ref<PG_FS> fs) {
	return PG_Types::mk_ref<PG_FileLogger>(msgr, fs);
}


PG_FileLogger::PG_FileLogger(Ref<PG_Msgr> msgr, Ref<PG_FS> fs) {
	_fs = fs;
	_msgr = msgr;
	_st_(Ref<PGW_Str> fp = PG_Paths::log_file_path());
	if (fp->ok()) { // TODO CHANGE TO NEG, ONLY HERE TO CHECK ERROR HANDLING
		_st_(_msgr->bcast(PGE_MsgLevel::ERROR, "START_LOG", fp->r()));
		return;
	}
	_st_(Ref<PGW_Str> md_dt = _fs->get_fmt_md_dt(fp->r(), true));

	// DOC: No need to check for validity of 'md_dt' since we always get
	// a return value thanks to get_fmt_md_dt()'s second argument set to true.
	_st_(Ref<PGW_Str> nn = PG_Paths::old_log_file_path(md_dt->r()));

	_if_st_(!_fs->rn_or_rm(fp->r(), nn->r())) {
		_st_(_msgr->bcast(PGE_MsgLevel::ERROR, "START_LOG", fp->r()));
		return;
	}

	_msgr->mk_tgt("file", callable_mp(this, &PG_FileLogger::_write), PGE_MsgLevel::INFO, PGE_MsgLevel::FATAL, true);
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
