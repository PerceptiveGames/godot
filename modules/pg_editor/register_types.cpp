/* register_types.cpp */


#include "register_types.h"
#include "core/object/class_db.h"
#include "editor/plugins/node_3d_editor_plugin.h"

//#ifdef TOOLS_ENABLED
#include "pgn_resizable_box.h"
#include "pgn_generic_editor_plugin.h"
//#endif


void initialize_pg_editor_module(ModuleInitializationLevel p_level) {
	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
		ClassDB::register_class<PGN_ResizableBox>();
	}
	else if (p_level == MODULE_INITIALIZATION_LEVEL_EDITOR) {
		// DOC: We cannot directly instantiate 'PGN_ResizableBoxGizmoPlugin' here.
		//		We have to go through an EditorPlugin. The issue is Godot's loading order,
		//		but there is nothing we can realistically do.
		EditorPlugins::add_by_type<PGN_GenericEditorPlugin>();
	}
}


void uninitialize_pg_editor_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}
