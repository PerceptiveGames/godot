#include "core/object/class_db.h"
#include "core/object/object.h"
#include "core/variant/callable.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/exts/pg_node_3d.h"
#include "modules/pg_g1/types/pg_typedefs.h"
#include "scene/3d/node_3d.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


// DOC: 'f' takes two Node3Ds as mandatory params.
// DOC: Arg type is not 'Node' because callable might need to access
// properties specific to Node3D.
// TODO: Prefer a cast to Node3D inside callable, and keep arg as Node?
// NOPE, because of slicing.
// WAIT, slicing in on objects, not pointers. But this is a ref, soooo.
// Will it work?
void PG_Node3D::sort_children(Node3D &p, const Callable &f) {
	TA<Node3D> cs = p.get_children();
	cs.sort_custom(f);
	for (int i : cs) {
		p.move_child(Object::cast_to<Node3D>(cs.get(i)), i);
	}
}


//////////////////////////////////////////////////


#ifdef PG_GD_FNS
void PG_Node3D::_bind_methods() {
	// TODO: FIX.
	//ClassDB::bind_static_method("PG_Node3D", D_METHOD("sort_children", "p", "f"), &PG_Node3D::sort_children);
}
#endif


//////////////////////////////////////////////////
//////////////////////////////////////////////////
