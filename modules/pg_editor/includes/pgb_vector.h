#include "modules/register_module_types.h"
#include "core/math/vector3.h"

#ifndef PGB_VECTOR3_H
#define PGB_VECTOR3_H

#include "core/templates/local_vector.h"
#include "scene/3d/node_3d.h"

class PGB_Vec3 : public Object {
	GDCLASS(PGB_Vec3, Object);

public:
	static Vector3 &set_x(Vector3 v, float new_x);
	static Vector3 &set_y(Vector3 v, float new_x);
	static Vector3 &set_z(Vector3 v, float new_x);
};

#endif // PGB_VECTOR3_H
