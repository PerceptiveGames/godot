#include "core/config/engine.h"
#include "core/object/class_db.h"
#include "core/object/ref_counted.h"
#include "core/os/memory.h"
#include "editor/editor_interface.h"
#include "modules/pg_g1/core/pg_cmds.h"
#include "modules/pg_g1/core/pg_fs.h"
#include "modules/pg_g1/core/pg_msgr.h"
#include "modules/pg_g1/core/pg_scene_tree.h"
#include "modules/pg_g1/core/pg_sys.h"
#include "modules/pg_g1/core/pg_time.h"
#include "modules/pg_g1/core/pg_timers.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/data/pg_paths.h"
#include "modules/pg_g1/exts/pg_num.h"
#include "modules/pg_g1/exts/pg_raycast.h"
#include "modules/pg_g1/exts/pg_rgx.h"
#include "modules/pg_g1/signals/pg_signals_user.h"
#include "modules/pg_g1/user/pg_session.h"
#include "scene/3d/camera_3d.h"
#include "scene/main/node.h"
#include "scene/main/viewport.h"
#include "scene/resources/3d/world_3d.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


PG_SceneTree *PG_SceneTree::get_sng() {
	return _singleton;
}


//////////////////////////////////////////////////


PG_SceneTree *PG_SceneTree::get_PG_SceneTree() {
	return _singleton;
}


Ref<PG_Sys> PG_SceneTree::get_PG_Sys() {
	return _pg_sys;
}


Ref<PG_FS> PG_SceneTree::get_PG_FS() {
	return _pg_fs;
}


PG_Time *PG_SceneTree::get_PG_Time() {
	return _pg_time;
}


Ref<PG_Timers> PG_SceneTree::get_PG_Timers() {
	return _pg_timers;
}


Ref<PG_Msgr> PG_SceneTree::get_PG_Msgr() {
	return _pg_msgr;
}


Ref<PG_Cmds> PG_SceneTree::get_PG_Cmds() {
	return _pg_cmds;
}


Ref<PG_SignalsUser> PG_SceneTree::get_PG_SignalsUser() {
	return _pg_sgns_user;
}


//////////////////////////////////////////////////


Node *PG_SceneTree::pg_get_root() {
	if (PG_IS_EDITOR) {
		return get_edited_scene_root();
	} else { // DOC: Explicit 'else' may help with compiler optimization here?
		// TODO: Safe?
		return (Node*)get_root();
	}
}


bool PG_SceneTree::pg_is_paused() {
	return is_paused();
}


//////////////////////////////////////////////////


// DOC: Returns a SubViewport in GD, so we could retrieve the .size property.
// Wasn't used in GD code anywhere tho. So maybe returning just a Viewport is ok.
Viewport *PG_SceneTree::pg_get_viewport(int ed_idx) {
	if (PG_IS_EDITOR) {
		return EditorInterface::get_singleton()->get_editor_viewport_3d(ed_idx);
	}
	return pg_get_root()->get_viewport();
}


Ref<World3D> PG_SceneTree::get_world_3d(int ed_idx) {
	return pg_get_viewport(ed_idx)->get_world_3d();
}


Camera3D *PG_SceneTree::get_main_cam(int ed_idx) {
	return pg_get_viewport(ed_idx)->get_camera_3d();
}


Vector2 PG_SceneTree::get_mouse_pos(int ed_idx) {
	return pg_get_viewport(ed_idx)->get_mouse_position();
}


//////////////////////////////////////////////////


void PG_SceneTree::_bind_methods() {
#ifdef PG_GD_FNS
	ClassDB::bind_static_method("PG_SceneTree", D_METHOD("get_pg_scene_tree"), &PG_SceneTree::get_PG_SceneTree);
	ClassDB::bind_method(D_METHOD("get_pg_sys"), &PG_SceneTree::get_PG_Sys);
	ClassDB::bind_method(D_METHOD("get_pg_fs"), &PG_SceneTree::get_PG_FS);
	ClassDB::bind_method(D_METHOD("get_pg_time"), &PG_SceneTree::get_PG_Time);
	ClassDB::bind_method(D_METHOD("get_pg_timers"), &PG_SceneTree::get_PG_Timers);
	ClassDB::bind_method(D_METHOD("get_pg_msgr"), &PG_SceneTree::get_PG_Msgr);
	ClassDB::bind_method(D_METHOD("get_pg_cmds"), &PG_SceneTree::get_PG_Cmds);
	ClassDB::bind_method(D_METHOD("get_pg_"), &PG_SceneTree::get_PG_SignalsUser);

	ClassDB::bind_method(D_METHOD("pg_get_root"), &PG_SceneTree::pg_get_root);
	ClassDB::bind_method(D_METHOD("pg_is_paused"), &PG_SceneTree::pg_is_paused);

	ClassDB::bind_method(D_METHOD("pg_get_viewport", "ed_idx"), &PG_SceneTree::pg_get_viewport, DEFVAL(0));
	ClassDB::bind_method(D_METHOD("get_world_3d", "ed_idx"), &PG_SceneTree::get_world_3d, DEFVAL(0));
	ClassDB::bind_method(D_METHOD("get_main_cam", "ed_idx"), &PG_SceneTree::get_main_cam, DEFVAL(0));
	ClassDB::bind_method(D_METHOD("get_mouse_pos", "ed_idx"), &PG_SceneTree::get_mouse_pos, DEFVAL(0));
#endif
}


PG_SceneTree::PG_SceneTree() {
	// TODO (OLD?):
	// For each singleton s below
	//   If in-editor singleton 'es' inheriting from s exists
	//     Get singleton 'es' and assign it to the field assigned to s
	//   Else
	//     Assign s like below
	//
	// Since 'es' does not exist at this point in the ctor, either (1) defer assignment of 'es' to s,
	// or (2) init below, and then init 'es' and assign vars from s to 'es', and then get rid of s.

	// TODO (OLD?): Maybe have sys, fs, time, timers, msgr, cmds not be singletons and be members of 'sys' or new 'core'
	// singleton instead. rgx, num can be members of a new exts singleton.

	if (PG_S(Engine)->is_editor_hint()) {
		return;
	}

	_singleton = this;

	// DOC: Keep as high in the list as possible because it needs to run signals as early as possible.
	_pg_sys = PG_Sys::mk(this);
	_pg_time = PG_Time::mk(this);
	_pg_msgr = PG_Msgr::mk();
	_pg_timers = PG_Timers::mk(this, _pg_time, _pg_msgr);
	_pg_fs = PG_FS::mk(_pg_msgr, _pg_timers);
	_pg_cmds = PG_Cmds::mk();
	_pg_session = PG_Session::mk(_pg_msgr, _pg_fs, _pg_cmds);
	_pg_sgns_user = PG_SignalsUser::mk();


	// DOC: It's more logical to me to call a function that is setting 'msgr' from here,
	// rather than have each class access the PG_SceneTree singleton.
	PG_Num::init();
	PG_Paths::set_fs(_pg_fs);
	PG_Rgx::set_msgr(_pg_msgr);
	PG_Raycast::set_stree(this);

	for (Variant v : pg_get_root()->get_children(true)) {
		Node *n = Object::cast_to<Node>(v);
		// ERR_PRINT(vformat("%s\n", n->get_name()));
		// ERR_PRINT(n->get_name());
		print_line(n->get_name());
	}
}


PG_SceneTree::~PG_SceneTree() {
	memdelete(_pg_time);
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
