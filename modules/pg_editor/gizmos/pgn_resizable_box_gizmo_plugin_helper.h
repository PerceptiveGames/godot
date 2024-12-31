/**************************************************************************/
/*  pgn_resizable_box_gizmo_plugin_helper.h                               */
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


#ifndef PGN_RESIZABLE_BOX_GIZMO_PLUGIN_HELPER_H
#define PGN_RESIZABLE_BOX_GIZMO_PLUGIN_HELPER_H

#include "core/object/ref_counted.h"


class Camera3D;


class PGN_ResizableBoxGizmoPluginHelper : public RefCounted {
	GDCLASS(PGN_ResizableBoxGizmoPluginHelper, RefCounted);

	int current_handle_id;
	Variant initial_value;
	Transform3D initial_transform;


public:
	void initialize_handle_action(const Variant &p_initial_value, const Transform3D &p_initial_transform);

	void get_segment(Camera3D *p_camera, const Point2 &p_point, Vector3 *r_segment);

	Vector<Vector3> box_get_handles(const Vector3 &p_box_size, const bool has_x_handles, const bool has_y_handles, const bool has_z_handles);
	String box_get_handle_name(int p_id) const;
	void box_set_handle(const Vector3 p_segment[2], int p_id, Vector3 &r_box_size, Vector3 &r_box_position);
	void box_commit_handle(const String &p_action_name, bool p_cancel, Object *p_position_object, Object *p_size_object = nullptr, const StringName &p_position_property = "global_position", const StringName &p_size_property = "size");
};

#endif // PGN_RESIZABLE_BOX_GIZMO_PLUGIN_HELPER_H
