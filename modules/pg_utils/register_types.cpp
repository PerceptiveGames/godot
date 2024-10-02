/* register_types.cpp */

#include "register_types.h"
#include "core/object/class_db.h"

#include "pg_array.h"


void initialize_pg_utils_module(ModuleInitializationLevel p_level) {
	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
		ClassDB::register_class<PGArray>();
	}
}


void uninitialize_pg_utils_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}
