#include "core/error/error_list.h"
#include "core/io/dir_access.h"
#include "core/io/file_access.h"
#include "core/object/ref_counted.h"
#include "core/string/string_name.h"
#include "core/string/ustring.h"
#include "core/templates/vector.h"
#include "core/variant/callable.h"
#include "core/variant/typed_array.h"
#include "core/variant/variant.h"
#include "core/variant/variant_utility.h"
#include "modules/pg_g1/core/pg_msgr.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/exts/pg_arr.h"
#include "modules/pg_g1/exts/pg_sn.h"
#include "modules/pg_g1/types/pg_types.h"
#include "modules/pg_g1/exts/pg_str.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


String PGE_MsgLevelStr(PGE_MsgLevel lvl) {
	if (lvl == 1) { return "INPUT"; }
	if (lvl == 2) { return "INFO"; }
	if (lvl == 3) { return "WARNING"; }
	if (lvl == 4) { return "ERROR"; }
	if (lvl == 5) { return "INPUT_VIP"; }
	if (lvl == 6) { return "INFO_VIP"; }
	if (lvl == 7) { return "WARNING_VIP"; }
	if (lvl == 8) { return "FATAL"; }
	return "NONE";
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////


String PG_Msgs::get(StringName k) const {
	if (_m.has(k)) {
		return _m[k];
	}
	return k;
}


//////////////////////////////////////////////////


Ref<PG_Msgs> PG_Msgs::mk() {
	return PG_Types::mk_ref<PG_Msgs>();
}


PG_Msgs::PG_Msgs() {
	// TODO: Maybe: "MAKE SURE THAT THE FILE IS NOT OPEN IN ANY PROGRAM..."
	const String file_perms = "MAKE SURE THAT NO OTHER PROGRAM (SUCH AS NOTEPAD) IS USING THE FILE AND THAT YOU HAVE WRITE PERMISSIONS ON THE FOLDER.";
	const String dir_perms = "MAKE SURE THAT NO OTHER PROGRAM IS USING THE FOLDER AND THAT YOU HAVE WRITE PERMISSIONS ON THE FOLDER.";
	const String parent_dir_perms = "MAKE SURE THAT NO OTHER PROGRAM IS USING THE FOLDER AND THAT YOU HAVE WRITE PERMISSIONS ON THE PARENT FOLDER.";

	_m["FILE_NOT_EXIST"] = "FILE '{arg}' DOES NOT EXIST.";
	_m["MK_FILE"] = "UNABLE TO CREATE FILE '{arg}'. ERROR: '{err}'. " + file_perms;
	_m["OPEN_FILE"] = "UNABLE TO OPEN FILE '{arg}'. ERROR: '{err}'. " + file_perms;
	_m["CLOSE_FILE_ALREADY_CLOSED"] = "ATTEMPTED TO CLOSE FILE '{arg}', BUT IT HAD ALREADY BEEN CLOSED PREVIOUSLY.";
	_m["CLOSE_FILE_IMPROPER"] = "ATTEMPTED TO CLOSE FILE '{arg}', BUT IT WAS ALREADY CLOSED, ALTHOUGH IMPROPERLY. THE STANDARD FUNCTIONS FROM THE CUSTOM 'FILESYSTEM' CLASS SHOULD ALWAYS BE USED FOR FILE MANIPULATION.";
	_m["CLOSE_FILE_NEVER_OPENED"] = "ATTEMPTED TO CLOSE FILE '{arg}', BUT IT WAS NEVER OPENED IN THE FIRST PLACE.";
	_m["TRUNC_FILE"] = "UNABLE TO TRUNCATE FILE '{arg}'. ERROR: '{err}'. " + file_perms;
	_m["SAVE_FILE"] = "UNABLE TO SAVE FILE '{arg}'. ERROR: '{err}'. " + file_perms;
	_m["RM_FILE"] = "UNABLE TO DELETE FILE '{arg}'. ERROR: '{err}'. " + file_perms;

	_m["RN_FILE_OPEN"] = "UNABLE TO RENAME FILE '{arg}' TO '{arg}' BECAUSE THE FILE IS CURRENTLY OPEN.";
	_m["RN_OR_TRASH_FILE"] = "UNABLE TO RENAME FILE '{arg}' TO '{arg}'. ERROR: '{err}'. ATTEMPTING TO MOVE FILE TO TRASH/RECYCLE BIN INSTEAD...";
	_m["TRASH_OR_RM_FILE"] = "UNABLE TO MOVE FILE '{arg}' TO TRASH/RECYCLE BIN. ATTEMPTING DELETION INSTEAD...";
	_m["TRASH_FILE_OK"] = "FILE '{arg}' WAS MOVED TO TRASH/RECYCLE BIN SUCCESSFULLY, OR PERMANENTLY DELETED IF NO TRASH/RECYCLE BIN PRESENT OR ENABLED ON SYSTEM.";
	_m["RM_FILE_OK"] = "FILE '{arg}' DELETED SUCCESSFULLY.";

	_m["START_LOG"] = "UNABLE TO START LOGGING TO FILE '{arg}'. FILE LOGGING WILL BE DISABLED FOR THE ENTIRE DURATION OF THE SESSION.";

	_m["OPEN_DIR"] = "UNABLE TO OPEN FOLDER '{arg}'. ERROR: '{err}'. " + dir_perms;
	_m["RD_DIR"] = "UNABLE TO READ FOLDER '{arg}'. ERROR: '{err}'. " + dir_perms;
	_m["MK_DIR"] = "UNABLE TO CREATE FOLDER '{arg}'. ERROR: '{err}'. " + parent_dir_perms;

	_m["FILE_MD_DT"] = "UNABLE TO RETRIEVE MODIFICATION DATE AND TIME FOR FILE '{arg}'.";

	_m["RESIZE_ARR"] = "UNABLE TO RESIZE ARRAY. ERROR: '{err}'.";

	_m["INPUT_WRONG_UNLOAD"] = "UNLOADED KEYBIND SET '{arg}', BUT EXPECTED KEYBIND SET TO BE '{arg}'. INPUT IS LIKELY TO BE UNRESPONSIVE OR UNEXPECTED.";
	_m["INPUT_NO_SET"] = "STACK OF KEYBIND SETS IS EMPTY, BUT SHOULD NOT BE. INPUT IS LIKELY TO BE UNRESPONSIVE OR UNEXPECTED.";
	_m["INPUT_CFG_LOAD"] = "UNABLE TO LOAD INPUT CONFIGURATION FILE '{arg}'. ERROR: '{err}'.";
	_m["INPUT_CFG_SAVE"] = "UNABLE TO SAVE INPUT CONFIGURATION FILE '{arg}'. ERROR: '{err}'.";
	_m["INPUT_CFG_PARSE"] = "UNABLE TO PARSE INPUT CONFIGURATION FILE '{arg}'. ERROR: '{err}'.";
	_m["INPUT_CFG_VER"] = "INPUT CONFIGURATION FILE '{arg}' CONTAINS INVALID PARSER VERSION INFORMATION.";
	_m["INPUT_CFG_RN_OR_RM"] = "ATTEMPTING TO RENAME FAULTY EXISTING INPUT CONFIGURATION FILE '{arg}' TO '{arg}' AND RECREATE NEW FILE '{arg}' WITH DEFAULT VALUES.";
	_m["INPUT_CFG_DISABLED"] = "ALL ATTEMPTS TO HANDLE CONFIGURATION FILE HAVE FAILED. OPERATIONS ON THE FILE WILL BE DISABLED FOR THE ENTIRE DURATION OF THE SESSION.";

	_m["TIMER_STARTED_IN_START"] = "ATTEMPTED TO START TIMER '{arg}', BUT IT HAD ALREADY BEEN STARTED.";
	_m["TIMER_RUNNING_IN_START"] = "ATTEMPTED TO START TIMER '{arg}', BUT IT HAD ALREADY BEEN STARTED AND RUNNING.";
	_m["TIMER_NOT_STARTED_IN_PAUSE"] = "ATTEMPTED TO PAUSE TIMER '{arg}', BUT IT HADN'T BEEN STARTED.";
	_m["TIMER_NOT_RUNNING_IN_PAUSE"] = "ATTEMPTED TO PAUSE TIMER '{arg}', WHICH HAD BEEN STARTED BUT WASN'T RUNNING.";
	_m["TIMER_NOT_STARTED_IN_RESUME"] = "ATTEMPTED TO RESUME TIMER '{arg}', BUT IT HADN'T BEEN STARTED.";
	_m["TIMER_RUNNING_IN_RESUME"] = "ATTEMPTED TO RESUME TIMER '{arg}', BUT IT HAD ALREADY BEEN STARTED AND RUNNING.";
	_m["TIMER_NOT_STARTED_IN_RESTART"] = "ATTEMPTED TO RESTART TIMER '{arg}', BUT IT HADN'T BEEN STARTED.";
	_m["TIMER_F_CALL_IN_CALLBACK"] = "ERROR ON TIMER '{arg}'. CALLING A TIMER CONTROL FUNCTION INSIDE OF ONE OF ITS OWN CALLBACK FUNCTIONS IS PROHIBITED. TRY A DEFERRED CALL OR DELAY ITS EXECUTION UNTIL THE NEXT FRAME.";
	_m["TIMER_INSTANCE_PROCESS_MODE"] = "'NODE.PROCESS_MODE' ERROR IN TIMER '{arg}'. 'NODE.PROCESS_MODE_INHERIT' SELECTED, BUT '_PROCESS_MODE_PARENT' NODE IS NULL.";

	_m["RGX_COMPILE"] = "REGEX COMPILATION FAILED. REGEX: -> {arg} <-. ERROR: {err}.";

	_m["SGN_CONNECT"] = "COULD NOT CONNECT METHOD '{arg}' TO SIGNAL '{arg}'. ERROR: {err}.";

	_m["STACK_TRACE"] = "STACK TRACE:\n{arg}";
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////


Ref<PG_MsgrTgt> PG_Msgr::mk_tgt(StringName id, const Callable &f, int min_lvl, int max_lvl, bool is_enabled) {
	return PG_MsgrTgt::mk(id, f, min_lvl, max_lvl, is_enabled);
}


//////////////////////////////////////////////////


Ref<PG_Msg> PG_Msgr::mk_msg(PGE_MsgLevel lvl, String tgt, StringName id, String txt, Error e) {
	Vector<StringName> t = (tgt[0] == '-') ? PG_SN::mk_vec_sn("-", tgt.substr(1)) : PG_SN::mk_vec_sn(tgt);
	return mk_msg(lvl, t, id, txt, e);
}


// TODO: Try to create PG_Msg ctor, then use instantiate() with args.
Ref<PG_Msg> PG_Msgr::mk_msg(PGE_MsgLevel lvl, Vector<StringName> tgts, StringName id, String txt, Error e) {
	Ref<PG_Msg> r;
	r.instantiate();
	r->lvl = lvl;
	r->tgts = tgts;
	r->id = id;
	r->txt = txt;
	r->e = e;
#ifdef PG_STACK_TRACE
	r->st = _get_st_;
#endif
	return r;
}


//////////////////////////////////////////////////


// TODO: Redirect/add additional redirect here of stderr and stdout.
// TODO: Keep track of repetitions to avoid outputting the same msgs hundreds of times.
// Simple "Too many errors. Reliability of game state not guaranteed going forward." messages that stays on screen at all times, after like 20 messages.
// Maybe allow x times the same id over a period of time.
Ref<PG_Msg> PG_Msgr::build(PGE_MsgLevel lvl, Vector<StringName> tgts, StringName id, Error e, TypedArray<String> strs) {
	//String prefix = _is_ready_for_pg_logging ? "[EARLY CODE] " : "";
	String txt = _msgs->get(id);

	if (id == "OPEN_DIR") {
		e = DirAccess::get_open_error();
	} else if (id == "MK_FILE" || id == "OPEN_FILE" || id == "TRUNC_FILE") {
		e = FileAccess::get_open_error();
	}

	for (int i = 0; i < strs.size(); ++i) {
		txt = txt.replace_first("{arg}", strs[i]);
	}

	if (e != Error::OK) {
		txt = txt.replace("{err}", VariantUtilityFunctions::error_string(e));
	}
	txt = txt.replace(" ERROR: '{err}'.", "");

#ifdef STACK_TRACE
	if (lvl >= PGE_MsgLevel::WARNING) {
		txt += "\n" + _msgs->get("STACK_TRACE").replace("{arg}", _join_st_);
	}
#endif // STACK_TRACE

	txt += "\n";
	return mk_msg(lvl, tgts, id, txt, e);
}


Ref<PG_Msg> PG_Msgr::bcast(PGE_MsgLevel lvl, StringName id) {
	return bcast(build(lvl, Vector<StringName>(), id, Error::OK, TypedArray<String>()));
}

Ref<PG_Msg> PG_Msgr::bcast(PGE_MsgLevel lvl, StringName id, String str) {
	return bcast(build(lvl, Vector<StringName>(), id, Error::OK, PG_Str::mk_ta_str(str)));
}

Ref<PG_Msg> PG_Msgr::bcast(PGE_MsgLevel lvl, StringName id, Error e, String str) {
	return bcast(build(lvl, Vector<StringName>(), id, e, PG_Str::mk_ta_str(str)));
}

Ref<PG_Msg> PG_Msgr::bcast(PGE_MsgLevel lvl, String tgt, StringName id, Error e, String str) {
	return bcast(build(lvl, PG_SN::mk_vec_sn(tgt), id, e, PG_Str::mk_ta_str(str)));
}

Ref<PG_Msg> PG_Msgr::bcast(PGE_MsgLevel lvl, Vector<StringName> tgts, StringName id, Error e, String str) {
	return bcast(build(lvl, tgts, id, e, PG_Str::mk_ta_str(str)));
}


Ref<PG_Msg> PG_Msgr::bcast(PGE_MsgLevel lvl, StringName id, TypedArray<String> strs) {
	return bcast(build(lvl, Vector<StringName>(), id, Error::OK, strs));
}

Ref<PG_Msg> PG_Msgr::bcast(PGE_MsgLevel lvl, StringName id, Error e, TypedArray<String> strs) {
	return bcast(build(lvl, Vector<StringName>(), id, e, strs));
}

Ref<PG_Msg> PG_Msgr::bcast(PGE_MsgLevel lvl, String tgt, StringName id, Error e, TypedArray<String> strs) {
	return bcast(build(lvl, PG_SN::mk_vec_sn(tgt), id, e, strs));
}

Ref<PG_Msg> PG_Msgr::bcast(PGE_MsgLevel lvl, Vector<StringName> tgts, StringName id, Error e, TypedArray<String> strs) {
	return bcast(build(lvl, tgts, id, e, strs));
}


Ref<PG_Msg> PG_Msgr::bcast(Ref<PG_Msg> msg) {
	if (msg->tgts.is_empty()) {
		for (int i = 0; i < _tgts.size(); ++i) {
			_tgts.getv(i)->send(msg);
		}
	} else if (msg->tgts[0] == "-") {
		for (int i = 0; i < _tgts.size(); ++i) {
			if (!msg->tgts.has(_tgts.getk(i))) {
				_tgts.getv(i)->send(msg);
			}
		}
	} else {
		for (int i = 0; i < msg->tgts.size(); ++i) {
			_tgts[msg->tgts[i]]->send(msg);
		}
	}
	return msg;
}


#ifdef PG_GD_FNS
Ref<PG_Msg> PG_Msgr::_gd_bcast(PGE_MsgLevel lvl, Vector<StringName> tgts, StringName id, Error e, TypedArray<String> strs) {
	return bcast(lvl, tgts, id, e, strs);
}
#endif


//////////////////////////////////////////////////


void PG_Msgr::_bind_methods() {
#ifdef PG_GD_FNS
	// TODO: UNCOMMENT AND FIX.
	//ClassDB::bind_static_method("PG_Msgr", D_METHOD("bcast", "lvl", "id", "str", "e", "vrt"), &PG_Msgr::_gd_bcast, DEFVAL(""), DEFVAL(Error::OK), DEFVAL(Variant::NIL));
#endif
}


Ref<PG_Msgr> PG_Msgr::mk() {
	return PG_Types::mk_ref<PG_Msgr>();
}


PG_Msgr::PG_Msgr() {
	_msgs = PG_Msgs::mk();

}


//////////////////////////////////////////////////
//////////////////////////////////////////////////


void PG_MsgrTgt::set_enabled(bool v) {
	_is_enabled = v;
}


//////////////////////////////////////////////////


void PG_MsgrTgt::send(Ref<PG_Msg> msg) {
	if (!_is_enabled || msg->lvl < _min_lvl || msg->lvl > _max_lvl) {
		return;
	}
	_f.call(msg);
}


//////////////////////////////////////////////////


Ref<PG_MsgrTgt> PG_MsgrTgt::mk(StringName id, const Callable &f, int min_lvl, int max_lvl, bool is_enabled) {
	return PG_Types::mk_ref<PG_MsgrTgt>(id, f, min_lvl, max_lvl, is_enabled);
}


PG_MsgrTgt::PG_MsgrTgt() :
		_id(StringName()),
		_f(nullptr),
		_min_lvl(-1),
		_max_lvl(-1),
		_is_enabled(false) {}


PG_MsgrTgt::PG_MsgrTgt(StringName id, const Callable &f, int min_lvl, int max_lvl, bool is_enabled) :
		_id(id),
		_f(f),
		_min_lvl(min_lvl),
		_max_lvl(max_lvl),
		_is_enabled(is_enabled) {}


//////////////////////////////////////////////////
//////////////////////////////////////////////////


PG_Msg::PG_Msg() :
	lvl(PGE_MsgLevel::NONE),
	e(Error::OK) {}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
