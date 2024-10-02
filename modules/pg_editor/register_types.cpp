/* register_types.cpp */

#include "register_types.h"
#include "core/object/class_db.h"
#include "editor/plugins/node_3d_editor_plugin.h"

//#ifdef TOOLS_ENABLED
#include "pgb_box.h"
#include "gizmos/pgepb_gizmos.h"
#include "pgb_wall.h"
//#endif


void initialize_pg_editor_module(ModuleInitializationLevel p_level) {
	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
		ClassDB::register_class<PGB_Box>();
		ClassDB::register_class<PGB_Wall>();
		ClassDB::register_class<PGB_WallCavity>();
	}
	else if (p_level == MODULE_INITIALIZATION_LEVEL_EDITOR) {
		EditorPlugins::add_by_type<PGEPB_Gizmos>();
	}
}


void uninitialize_pg_editor_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}
