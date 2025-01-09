#include "core/object/object.h"
#include "core/variant/variant.h"
#include "modules/pg_g1/data/pg_const.h"
#include "modules/pg_g1/data/pg_macros.h"


//////////////////////////////////////////////////
////////////////////////////////////////////////////


const float PG_Const::file_auto_close_delay = 30.0;


//////////////////////////////////////////////////


const int PG_Const::max_log_files = 10;


//////////////////////////////////////////////////


const int PG_Const::config_file_parser_version = 1;


//////////////////////////////////////////////////


const float PG_Const::interact_raycast_length = 1.0;


//////////////////////////////////////////////////


const int PG_Const::while_loop_low_limit = 100;
const int PG_Const::while_loop_mid_limit = 1000;
const int PG_Const::while_loop_high_limit = 10000;


//////////////////////////////////////////////////


// DOC: Used as a default ID value in files containing translatable strings.
const int PG_Const::default_po_id = 0;

void PG_Const::_bind_methods() {
#ifdef PG_GD_FNS
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "file_auto_close_delay"), "", "file_auto_close_delay");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "max_log_files"), "", "max_log_files");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "config_file_parser_version"), "", "config_file_parser_version");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "interact_raycast_length"), "", "interact_raycast_length");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "while_loop_low_limit"), "", "while_loop_low_limit");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "while_loop_mid_limit"), "", "while_loop_mid_limit");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "while_loop_high_limit"), "", "while_loop_high_limit");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "default_po_id"), "", "default_po_id");

#endif
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
