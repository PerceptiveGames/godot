/**************************************************************************/
/*  pgn_resizable_box_gizmo_plugin.cpp                                    */
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


#include "pgn_resizable_box_gizmo_plugin.h"
#include "pgn_resizable_box_gizmo_plugin_helper.h"
#include "../pgn_resizable_box.h"

#include "editor/inspector_dock.h"
#include "editor/editor_settings.h"
#include "editor/editor_undo_redo_manager.h"

//#include "editor/editor_log.h"
//#include "editor/editor_node.h"
//#include "scene/main/node.h"


bool PGN_ResizableBoxGizmoPlugin::has_gizmo(Node3D *p_spatial) {
	return Object::cast_to<PGN_ResizableBox>(p_spatial) != nullptr;
}

String PGN_ResizableBoxGizmoPlugin::get_gizmo_name() const {
	return "PGN_ResizableBoxGizmoPlugin";
}


int PGN_ResizableBoxGizmoPlugin::get_priority() const {
	return 10;
}


String PGN_ResizableBoxGizmoPlugin::get_handle_name(const EditorNode3DGizmo *p_gizmo, int p_id, bool p_secondary) const {
	return helper->box_get_handle_name(p_id);
}

Variant PGN_ResizableBoxGizmoPlugin::get_handle_value(const EditorNode3DGizmo *p_gizmo, int p_id, bool p_secondary) const {
	PGN_ResizableBox *box = Object::cast_to<PGN_ResizableBox>(p_gizmo->get_node_3d());

	if (box)
		return box->get_size();
	return Variant();
}


void PGN_ResizableBoxGizmoPlugin::begin_handle_action(const EditorNode3DGizmo *p_gizmo, int p_id, bool p_secondary) {
	PGN_ResizableBox *box = Object::cast_to<PGN_ResizableBox>(p_gizmo->get_node_3d());

	helper->initialize_handle_action(get_handle_value(p_gizmo, p_id, p_secondary), box->get_global_transform());

	box->emit_signal("begin_handle_moved");
}

void PGN_ResizableBoxGizmoPlugin::set_handle(const EditorNode3DGizmo *p_gizmo, int p_id, bool p_secondary, Camera3D *p_camera, const Point2 &p_point) {
	PGN_ResizableBox *box = Object::cast_to<PGN_ResizableBox>(p_gizmo->get_node_3d());

	Vector3 sg[2];
	helper->get_segment(p_camera, p_point, sg);

	Vector3 size = box->get_size();
	Vector3 position;
	Vector3 offset;
	helper->box_set_handle(sg, p_id, size, position);
	box->set_size(size);
	box->set_global_position(position);

	box->emit_signal("handle_moved");

	// Added to allow refresh at each value change. Calls PGN_ResizableBoxGizmoPlugin::redraw() down the line.
	// https://github.com/godotengine/godot/issues/71979
	//box->update_gizmos();
}

void PGN_ResizableBoxGizmoPlugin::commit_handle(const EditorNode3DGizmo *p_gizmo, int p_id, bool p_secondary, const Variant &p_restore, bool p_cancel) {
	PGN_ResizableBox *box = Object::cast_to<PGN_ResizableBox>(p_gizmo->get_node_3d());
	helper->box_commit_handle(TTR("Change Box Shape Size"), p_cancel, box, box);

	box->emit_signal("end_handle_moved");
}


void PGN_ResizableBoxGizmoPlugin::redraw(EditorNode3DGizmo *p_gizmo) {
	PGN_ResizableBox *box = Object::cast_to<PGN_ResizableBox>(p_gizmo->get_node_3d());

	p_gizmo->clear();
	const Ref<Material> material = get_material("shape_material", p_gizmo);
	Ref<Material> handles_material = get_material("handles");

	Vector<Vector3> lines;
	AABB aabb;
	aabb.position = Vector3(0, 0, 0);
	aabb.size = box->get_size();

	for (int i = 0; i < 12; i++) {
		Vector3 a, b;
		aabb.get_edge(i, a, b);
		lines.push_back(a);
		lines.push_back(b);
	}

	const Vector<Vector3> handles = helper->box_get_handles(box->get_size(), box->has_x_handles(), box->has_y_handles(), box->has_z_handles());

	p_gizmo->add_lines(lines, material);
	p_gizmo->add_collision_segments(lines);
	p_gizmo->add_handles(handles, handles_material);
}


PGN_ResizableBoxGizmoPlugin::PGN_ResizableBoxGizmoPlugin() {
	helper.instantiate();
	const Color gizmo_color = SceneTree::get_singleton()->get_debug_collisions_color();
	create_material("shape_material", gizmo_color);
	create_handle_material("handles");

	//InspectorDock::get_inspector_singleton()->connect("property_edited", callable_mp(this, &PGN_ResizableBoxGizmoPlugin::update_gizmos));
}

PGN_ResizableBoxGizmoPlugin::~PGN_ResizableBoxGizmoPlugin() {
}
