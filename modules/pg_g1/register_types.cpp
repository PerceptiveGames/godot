/* register_types.cpp */
#include "2d/pg_console.h"
#include "core/object/class_db.h"
#include "data/pg_const.h"
#include "exts/pg_sn.h"
#include "modules/pg_g1/core/pg_cmds.h"
#include "modules/pg_g1/core/pg_fs.h"
#include "modules/pg_g1/core/pg_msgr.h"
#include "modules/pg_g1/core/pg_scene_tree.h"
#include "modules/pg_g1/core/pg_sys.h"
#include "modules/pg_g1/core/pg_time.h"
#include "modules/pg_g1/core/pg_timers.h"
#include "modules/pg_g1/data/pg_paths.h"
#include "modules/pg_g1/exts/pg_arr.h"
#include "modules/pg_g1/exts/pg_dict.h"
#include "modules/pg_g1/exts/pg_node_3d.h"
#include "modules/pg_g1/exts/pg_node_3d_editor.h"
#include "modules/pg_g1/exts/pg_num.h"
#include "modules/pg_g1/exts/pg_raycast.h"
#include "modules/pg_g1/exts/pg_rgx.h"
#include "modules/pg_g1/exts/pg_str.h"
#include "modules/pg_g1/exts/pg_v2.h"
#include "modules/pg_g1/exts/pg_v3.h"
#include "modules/pg_g1/exts/pg_vec.h"
#include "modules/pg_g1/signals/pg_signals_user.h"
#include "modules/pg_g1/types/pg_pair.h"
#include "modules/pg_g1/types/pg_types.h"
#include "modules/pg_g1/types/pgw.h"
#include "modules/pg_g1/user/pg_cheats.h"
#include "modules/pg_g1/user/pg_config.h"
#include "modules/pg_g1/user/pg_input.h"
#include "modules/pg_g1/user/pg_profile.h"
#include "modules/pg_g1/user/pg_session.h"
#include "modules/pg_g1/user/pg_ui.h"
#include "modules/register_module_types.h"
#include "register_types.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


// TODO: If class is only used internally (e.g. PG_FileLogger),
// need to register still?


//////////////////////////////////////////////////
//////////////////////////////////////////////////


void initialize_pg_g1_module(ModuleInitializationLevel p_level) {
	if (p_level == MODULE_INITIALIZATION_LEVEL_CORE) {

		// NOTE: 2d folder
		ClassDB::register_class<PG_Console>();

		// NOTE: core folder
		ClassDB::register_class<PG_Cmds>();
		ClassDB::register_class<PG_Cmd>();

		ClassDB::register_class<PG_FS>();
		//ClassDB::register_class<PG_FileLogger>();

		ClassDB::register_class<PG_Msgr>();
		ClassDB::register_class<PG_MsgrTgt>();
		ClassDB::register_class<PG_Msgs>();
		ClassDB::register_class<PG_Msg>();

		ClassDB::register_class<PG_SceneTree>();

		ClassDB::register_class<PG_Sys>();

		ClassDB::register_class<PG_Time>();

		ClassDB::register_class<PG_Timers>();
		ClassDB::register_class<PG_Timer>();
		ClassDB::register_class<PG_TimerUnit>();
		ClassDB::register_class<PG_TimerSimple>();
		ClassDB::register_class<PG_TimerSimplePulse>();
		ClassDB::register_class<PG_TimerPulse>();
		ClassDB::register_class<PG_TimerInfinitePulse>();
		ClassDB::register_class<PG_TimerDeferredOneShot>();

		// NOTE: data folder
		ClassDB::register_class<PG_Const>();
		//ClassDB::register_class<PG_ST>();
		ClassDB::register_class<PG_Paths>();

		// NOTE: exts folder
		ClassDB::register_class<PG_Arr>();

		ClassDB::register_class<PG_Dict>();

		ClassDB::register_class<PG_Node3D>();

		ClassDB::register_class<PG_Node3DEditor>();

		ClassDB::register_class<PG_Num>();

		ClassDB::register_class<PG_Raycast>();
		ClassDB::register_class<PG_RaycastResult>();

		ClassDB::register_class<PG_Rgx>();

		ClassDB::register_class<PG_SN>();

		ClassDB::register_class<PG_Str>();

		ClassDB::register_class<PG_V2>();

		ClassDB::register_class<PG_V3>();

		ClassDB::register_class<PG_Vec>();

		// NOTE: signals folder
		ClassDB::register_class<PG_SignalsUser>();

		// NOTE: types folder
		ClassDB::register_class<PG_Pair>();

		ClassDB::register_class<PG_Types>();

		ClassDB::register_class<PGW_Arr>();
		ClassDB::register_class<PGW_ArrStr>();
		ClassDB::register_class<PGW_Dict>();
		ClassDB::register_class<PGW_Int>();
		ClassDB::register_class<PGW_Str>();
		ClassDB::register_class<PGW_VecStr>();
		ClassDB::register_class<PGW_Vrt>();

		// NOTE: user folder
		ClassDB::register_class<PG_Cheats>();
		ClassDB::register_class<PG_Config>();
		ClassDB::register_class<PG_Input>();
		ClassDB::register_class<PG_Profile>();
		ClassDB::register_class<PG_Session>();
		ClassDB::register_class<PG_UI>();
	}
	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
		//ClassDB::register_class<PGV<TypedArray<String>>();
	}
}


void uninitialize_pg_g1_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
