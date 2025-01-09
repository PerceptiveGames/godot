#include "core/object/ref_counted.h"
#include "modules/pg_g1/core/pg_scene_tree.h"
#include "modules/pg_g1/core/pg_sys.h"
#include "modules/pg_g1/types/pg_types.h"
#include "scene/main/node.h"
#include "core/object/class_db.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


void PG_Sys::quit() {
	_stree->pg_get_root()->propagate_notification(Node::NOTIFICATION_WM_CLOSE_REQUEST);
	_stree->quit();
}


// TODO: Add a KILL
void PG_Sys::force_quit() {
	_stree->quit();
}


//////////////////////////////////////////////////


void PG_Sys::_bind_methods() {
#ifdef PG_GD_FNS
	ClassDB::bind_method(D_METHOD("quit"), &PG_Sys::quit);
	ClassDB::bind_method(D_METHOD("force_quit"), &PG_Sys::force_quit);
#endif
}


Ref<PG_Sys> PG_Sys::mk(PG_SceneTree *stree) {
	return PG_Types::mk_ref<PG_Sys>(stree);
}


PG_Sys::PG_Sys() {}


PG_Sys::PG_Sys(PG_SceneTree *stree) {
	_stree = stree;
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
