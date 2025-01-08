#ifndef PG_RAYCAST_H
#define PG_RAYCAST_H

#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "servers/physics_server_3d.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class Camera3D;
class ObjectID;
class RID;
struct Vector3;

class PG_RaycastResult;
class PG_SceneTree;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Raycast : public Object {
	GDCLASS(PG_Raycast, Object);
	PG_BIND;


//////////////////////////////////////////////////


protected:
	inline static PG_SceneTree *_stree;


public:
	static void set_stree(PG_SceneTree *stree);


//////////////////////////////////////////////////


public:
	static Ref<PG_RaycastResult> from_cursor(float len, const Camera3D *cam = nullptr);
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_RaycastResult : public RefCounted {
	GDCLASS(PG_RaycastResult, RefCounted);


//////////////////////////////////////////////////


public:
	const Vector3 position;
	const Vector3 normal;
	const RID rid;
	const ObjectID collider_id;
	const Object *collider = nullptr;
	const int shape = 0;
	const int face_index = -1;


//////////////////////////////////////////////////


public:
	PG_RaycastResult();

	PG_RaycastResult(const PhysicsDirectSpaceState3D::RayResult r);

	PG_RaycastResult(const Vector3 _position, const Vector3 _normal,
			const RID _rid, const ObjectID _collider_id,
			const Object *_collider = nullptr, const int _shape = 0,
			const int _face_index = -1);
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_RAYCAST_H
