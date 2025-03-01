#include "core/object/class_db.h"
#include "core/object/object.h"
#include "core/templates/vector.h"
#include "core/variant/array.h"
#include "core/variant/callable.h"
#include "core/variant/typed_array.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/exts/pg_arr.h"
#include "modules/pg_g1/exts/pg_node_3d.h"
#include "modules/pg_g1/exts/pg_vec.h"
#include "scene/3d/node_3d.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


// DOC: 'f' takes two Node3Ds as mandatory params.
// DOC: Arg type is not 'Node' because callable might need to access
// properties specific to Node3D.
// TODO: Prefer a cast to Node3D inside callable, and keep arg as Node?
// NOPE, because of slicing.
// WAIT, slicing is on objects, not pointers. But this is a ref, soooo.
// Will it work?
void PG_Node3D::sort_children(Node3D *p, const Callable &f) {
	if (p == nullptr) {
		// TODO: Add error message.
		return;
	}
	TypedArray<Node3D> cs = p->get_children();
	cs.sort_custom(f);
	for (int i : cs) {
		p->move_child(Object::cast_to<Node3D>(cs.get(i)), i);
	}
}


//////////////////////////////////////////////////


TypedArray<Node3D> PG_Node3D::to_arr_of_node_3d(const Array &a) {
	return PG_Arr::assign<Node3D>(a);
}  


//////////////////////////////////////////////////


void PG_Node3D::_bind_methods() {
#ifdef PG_GD_FNS
	ClassDB::bind_static_method("PG_Node3D", D_METHOD("sort_children", "p", "f"), &PG_Node3D::sort_children);
	ClassDB::bind_static_method("PG_Node3D", D_METHOD("to_arr_of_node_3d", "p", "f"), &PG_Node3D::to_arr_of_node_3d);
#endif
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
