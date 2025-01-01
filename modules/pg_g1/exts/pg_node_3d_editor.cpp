#include "core/math/math_defs.h"
#include "core/object/class_db.h"
#include "core/variant/dictionary.h"
#include "editor/plugins/node_3d_editor_plugin.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/exts/pg_node_3d_editor.h"
#include "modules/pg_g1/types/pg_typedefs.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


float PG_Node3DEditor::get_snap_translate() {
	return Node3DEditor::get_singleton()->get_state()["translate_snap"];
}

float PG_Node3DEditor::get_snap_rotate() {
	return Node3DEditor::get_singleton()->get_state()["rotate_snap"];
}

float PG_Node3DEditor::get_snap_scale() {
	return Node3DEditor::get_singleton()->get_state()["scale_snap"];
}


void PG_Node3DEditor::set_snap_translate(real_t v) {
	Dictionary d;
	d["translate_snap"] = v;
	Node3DEditor::get_singleton()->set_state(d);
}

void PG_Node3DEditor::set_snap_rotate(real_t v) {
	Dictionary d;
	d["rotate_snap"] = v;
	Node3DEditor::get_singleton()->set_state(d);
}

void PG_Node3DEditor::set_snap_scale(real_t v) {
	Dictionary d;
	d["scale_snap"] = v;
	Node3DEditor::get_singleton()->set_state(d);
}


//////////////////////////////////////////////////


#ifdef PG_GD_FNS
void PG_Node3DEditor::_bind_methods() {
	ClassDB::bind_static_method("PG_Node3DEditor", D_METHOD("get_snap_translate"), &PG_Node3DEditor::get_snap_translate);
	ClassDB::bind_static_method("PG_Node3DEditor", D_METHOD("set_snap_translate", "value"), &PG_Node3DEditor::set_snap_translate);
	ClassDB::bind_static_method("PG_Node3DEditor", D_METHOD("get_snap_rotate"), &PG_Node3DEditor::get_snap_rotate);
	ClassDB::bind_static_method("PG_Node3DEditor", D_METHOD("set_snap_rotate", "value"), &PG_Node3DEditor::set_snap_rotate);
	ClassDB::bind_static_method("PG_Node3DEditor", D_METHOD("get_snap_scale"), &PG_Node3DEditor::get_snap_scale);
	ClassDB::bind_static_method("PG_Node3DEditor", D_METHOD("set_snap_scale", "value"), &PG_Node3DEditor::set_snap_scale);
}
#endif


//////////////////////////////////////////////////
//////////////////////////////////////////////////
