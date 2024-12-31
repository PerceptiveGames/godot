#include "core/math/vector2.h"
#include "core/math/vector3.h"
#include "core/object/class_db.h"
#include "core/object/object.h"
#include "core/object/object_id.h"
#include "core/object/ref_counted.h"
#include "core/templates/rid.h"
#include "modules/pg_g1/core/pg_scene_tree.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/exts/pg_raycast.h"
#include "modules/pg_g1/types/pg_typedefs.h"
#include "modules/pg_g1/types/pg_types.h"
#include "scene/3d/camera_3d.h"
#include "servers/physics_server_3d.h"
#include <cstdint>


//////////////////////////////////////////////////
//////////////////////////////////////////////////


void PG_Raycast::set_stree(PG_SceneTree *stree) {
	_stree = stree;
}


//////////////////////////////////////////////////


Ref<PG_RaycastResult> PG_Raycast::from_cursor(float len, const Camera3D *cam) {
	if (!cam) {
		cam = _stree->get_main_cam();
	}
	Vector2 pos = _stree->get_mouse_pos();

	Vector3 from = cam->project_ray_origin(pos);
	Vector3 to = from + cam->project_ray_normal(pos) * len;

//	PG_Debug.draw_line_absolute("any", from, to, Color.WHITE, 10)

	const Ref<PhysicsRayQueryParameters3D> q = PhysicsRayQueryParameters3D::create(from, to, UINT32_MAX, TA<RID>());

	// DOC: Uses global coordinates, not local to node.
	PhysicsDirectSpaceState3D::RayResult r;
	_stree->get_world_3d()->get_direct_space_state()->intersect_ray(q->get_parameters(), r);
	return PG_Types::mk_ref<PG_RaycastResult>(r);
}


//////////////////////////////////////////////////


#ifdef PG_GD_FNS
void PG_Raycast::_bind_methods() {
	ClassDB::bind_static_method("PG_Raycast", D_METHOD("from_cursor", "len", "cam"), &PG_Raycast::from_cursor);
}
#endif


//////////////////////////////////////////////////
//////////////////////////////////////////////////


PG_RaycastResult::PG_RaycastResult() {}


PG_RaycastResult::PG_RaycastResult(const PhysicsDirectSpaceState3D::RayResult r) :
	position(r.position),
	normal(r.normal),
	rid(r.rid),
	collider_id(r.collider_id),
	collider(r.collider),
	shape(r.shape),
		face_index(r.face_index) {}


PG_RaycastResult::PG_RaycastResult(const Vector3 _position, const Vector3 _normal,
	const RID _rid, const ObjectID _collider_id,
	const Object *_collider, const int _shape,
	const int _face_index) :
		position(_position),
		normal(_normal),
		rid(_rid),
		collider_id(_collider_id),
		collider(_collider),
		shape(_shape),
		face_index(_face_index) {}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
