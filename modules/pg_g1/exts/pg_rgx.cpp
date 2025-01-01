#include "core/error/error_list.h"
#include "core/object/class_db.h"
#include "core/object/ref_counted.h"
#include "core/templates/vmap.h"
#include "modules/pg_g1/core/pg_msgr.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/exts/pg_rgx.h"
#include "modules/pg_g1/types/pg_typedefs.h"
#include "modules/regex/regex.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


Ref<PG_Msgr> PG_Rgx::_msgr;

VMap<StringName, Ref<RegEx>> PG_Rgx::_rgxs;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


void PG_Rgx::set_msgr(Ref<PG_Msgr> msgr) {
	_msgr = msgr;
}


//////////////////////////////////////////////////


Ref<RegEx> PG_Rgx::mk(String ptrn) {
	Ref<RegEx> r;
	r.instantiate();
	if (Error e = r->compile(ptrn)) {
		_st_(_msgr->bcast(PGE_MsgLevel::ERROR, Vector<StringName>(), "RGX_COMPILE", e, ptrn));
	}
	return r;
}


//////////////////////////////////////////////////


bool PG_Rgx::has(StringName k, String st) {
	if (_rgxs.is_empty()) {
		_init();
	}
	return _rgxs[k]->search(st)->get_string(0) != "";
}


Ref<RegEx> PG_Rgx::get(StringName k) {
	if (_rgxs.is_empty()) {
		_init();
	}
	return _rgxs[k];
}


String PG_Rgx::sub(StringName k, String st, String c) {
	if (_rgxs.is_empty()) {
		_init();
	}
	return _rgxs[k]->sub(st, c, true);
}


//////////////////////////////////////////////////


void PG_Rgx::_bind_methods() {
#ifdef PG_GD_FNS
	ClassDB::bind_static_method("PG_Rgx", D_METHOD("mk", "ptrn"), &PG_Rgx::mk);

	ClassDB::bind_static_method("PG_Rgx", D_METHOD("has", "k", "st"), &PG_Rgx::has);
	ClassDB::bind_static_method("PG_Rgx", D_METHOD("get", "k"), &PG_Rgx::get);
	ClassDB::bind_static_method("PG_Rgx", D_METHOD("sub", "k", "st", "c"), &PG_Rgx::get);
#endif
}


void PG_Rgx::_init() {
	_st_(_rgxs["only_digits"] = mk("\\d+"));
	_st_(_rgxs["dbl_spaces"] = mk("\\s\\s+"));
	_st_(_rgxs["bbcode_tags"] = mk("\\[.*?\\]"));
	// DOC: e.g. "output_2024-12-19_07h53m32s"
	_st_(_rgxs["old_log_fmt"] = mk("output_[0-9]{4}-[0-9]{2}-[0-9]{2}_[0-9]{2}h[0-9]{2}m[0-9]{2}s.log"));
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
