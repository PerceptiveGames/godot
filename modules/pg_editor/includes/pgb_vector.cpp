#include "pgb_vector.h"


Vector3 &PGB_Vec3::set_x(Vector3 v, float new_x) {
	v.x = new_x;
	return v;
}


Vector3 &PGB_Vec3::set_y(Vector3 v, float new_y) {
	v.y = new_y;
	return v;
}


Vector3 &PGB_Vec3::set_z(Vector3 v, float new_z) {
	v.z = new_z;
	return v;
}

//Vector3 &Vector3::operator+=(const Vector3 &p_v) {
//	x += p_v.x;
//	y += p_v.y;
//	z += p_v.z;
//	return *this;
//}
