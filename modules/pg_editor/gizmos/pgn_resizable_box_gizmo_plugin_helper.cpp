/**************************************************************************/
/*  pgn_resizable_box_gizmo_plugin_helper.cpp                             */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/


#include "pgn_resizable_box_gizmo_plugin_helper.h"

#include "editor/plugins/node_3d_editor_plugin.h"
#include "scene/3d/camera_3d.h"
#include "editor/editor_undo_redo_manager.h"

//#include "editor/editor_node.h"


void PGN_ResizableBoxGizmoPluginHelper::initialize_handle_action(const Variant &p_initial_value, const Transform3D &p_initial_transform) {
	initial_value = p_initial_value;
	initial_transform = p_initial_transform;
}


void PGN_ResizableBoxGizmoPluginHelper::get_segment(Camera3D *p_camera, const Point2 &p_point, Vector3 *r_segment) {
	Transform3D gt = initial_transform;
	Transform3D gi = gt.affine_inverse();

	Vector3 ray_from = p_camera->project_ray_origin(p_point);
	Vector3 ray_dir = p_camera->project_ray_normal(p_point);

	r_segment[0] = gi.xform(ray_from);
	r_segment[1] = gi.xform(ray_from + ray_dir * 4096);
}


Vector<Vector3> PGN_ResizableBoxGizmoPluginHelper::box_get_handles(const Vector3 &p_box_size, const bool has_x_handles, const bool has_y_handles, const bool has_z_handles) {
	Vector<Vector3> handles;
	Vector3 s = p_box_size;

	if (has_x_handles) {
		handles.push_back(Vector3(0, s.y / 2, s.z / 2));
		handles.push_back(Vector3(s.x, s.y / 2, s.z / 2));
	}
	else {
		handles.push_back(Vector3(100000, 100000, 100000));
		handles.push_back(Vector3(100000, 100000, 100000));
	}
	if (has_y_handles) {
		handles.push_back(Vector3(s.x / 2, 0, s.z / 2));
		handles.push_back(Vector3(s.x / 2, s.y, s.z / 2));
	} else {
		handles.push_back(Vector3(100000, 100000, 100000));
		handles.push_back(Vector3(100000, 100000, 100000));
	}
	if (has_z_handles) {
		handles.push_back(Vector3(s.x / 2, s.y / 2, 0));
		handles.push_back(Vector3(s.x / 2, s.y / 2, s.z));
	} else {
		handles.push_back(Vector3(100000, 100000, 100000));
		handles.push_back(Vector3(100000, 100000, 100000));
	}

	return handles;
}

String PGN_ResizableBoxGizmoPluginHelper::box_get_handle_name(int p_id) const {
	switch (p_id) {
		case 0:
		case 1:
			return "Size X";
		case 2:
		case 3:
			return "Size Y";
		case 4:
		case 5:
			return "Size Z";
	}
	return "";
}

void PGN_ResizableBoxGizmoPluginHelper::box_set_handle(const Vector3 p_segment[2], int p_id, Vector3 &r_box_size, Vector3 &r_box_position) {
	int axis = p_id / 2;
	int sign = p_id % 2 * -2 + 1;
	sign *= -1;

	Vector3 initial_size = initial_value;

	// p_segment and axis_segment are two different segments defined by their two vertices.
	// p_segment goes from the point on the camera the user clicked (in world coords) to the clicked object.
	// axis_segment is long (8192 units) and basically represents the active axis itself.

	Vector3 axis_segment[2] = { initial_size / 2, initial_size / 2 };
	axis_segment[0][axis] = 4096.0;
	axis_segment[1][axis] = -4096.0;
	Vector3 ra, rb;
	Geometry3D::get_closest_points_between_segments(axis_segment[0], axis_segment[1], p_segment[0], p_segment[1], ra, rb);

	// ra and rb are two points. They represent the shortest segment between axis_segment and p_segment.
	// ra is the point along the active axis closest to where the mouse cursor is.
	// rb is the corresponding point along the segment from camera through the clicked object. We don't need rb here.

	// Adjust position.
	Vector3 offset;
	if (sign < 0) {
		offset[axis] = ra[axis];
	}
	r_box_position = initial_transform.xform(offset);

	// Calculate new size.
	r_box_size = initial_size;
	r_box_size[axis] = sign > 0 ? ra[axis] : r_box_size[axis] - ra[axis];

	// Snap to grid.
	if (Node3DEditor::get_singleton()->is_snap_enabled()) {
		real_t old_box_size = r_box_size[axis];
		r_box_size[axis] = Math::snapped(r_box_size[axis], Node3DEditor::get_singleton()->get_translate_snap());
		if (sign < 0 && r_box_size[axis] != old_box_size) {
			r_box_position[axis] = Math::snapped(r_box_position[axis], Node3DEditor::get_singleton()->get_translate_snap());
		}
	}

	// Prevent negative sizes.
	r_box_size[axis] = MAX(r_box_size[axis], 0.001);
}


void PGN_ResizableBoxGizmoPluginHelper::box_commit_handle(const String &p_action_name, bool p_cancel, Object *p_position_object, Object *p_size_object, const StringName &p_position_property, const StringName &p_size_property) {
	if (!p_size_object) {
		p_size_object = p_position_object;
	}

	if (p_cancel) {
		p_size_object->set(p_size_property, initial_value);
		p_position_object->set(p_position_property, initial_transform.get_origin());
		return;
	}

	EditorUndoRedoManager *ur = EditorUndoRedoManager::get_singleton();
	ur->create_action(p_action_name);
	ur->add_do_property(p_size_object, p_size_property, p_size_object->get(p_size_property));
	ur->add_do_property(p_position_object, p_position_property, p_position_object->get(p_position_property));
	//ur->add_do_method(p_size_object, "update_gizmos");
	ur->add_undo_property(p_size_object, p_size_property, initial_value);
	ur->add_undo_property(p_position_object, p_position_property, initial_transform.get_origin());
	//ur->add_undo_method(p_size_object, "update_gizmos");
	ur->commit_action();
}
