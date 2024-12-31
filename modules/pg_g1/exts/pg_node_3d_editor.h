#ifndef PG_NODE_3D_EDITOR_H
#define PG_NODE_3D_EDITOR_H

#include "core/math/math_defs.h"
#include "core/object/object.h"
#include "modules/pg_g1/data/pg_macros.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Node3DEditor: public Object {
	GDCLASS(PG_Node3DEditor, Object);
	PG_BIND;


//////////////////////////////////////////////////


public:
	static float get_snap_translate();
	static float get_snap_rotate();
	static float get_snap_scale();
	static void set_snap_translate(real_t v);
	static void set_snap_rotate(real_t v);
	static void set_snap_scale(real_t v);
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_NODE_3D_EDITOR_H
