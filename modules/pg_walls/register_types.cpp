/* register_types.cpp */


#include "register_types.h"
#include "core/object/class_db.h"

//#ifdef TOOLS_ENABLED
#include "pgn_wall.h"
#include "pgn_wall_gap.h"
//#endif


void initialize_pg_walls_module(ModuleInitializationLevel p_level) {
	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
		ClassDB::register_class<PGN_Wall>();
		ClassDB::register_class<PGN_WallGap>();
	}
}


void uninitialize_pg_walls_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}
