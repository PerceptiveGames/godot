/**************************************************************************/
/*  pgb_gizmo_box.cpp                                                     */
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

#include "pgb_gizmo_box.h"
#include "pgb_gizmo_box_helper.h"
#include "../pgb_box.h"

#include "editor/inspector_dock.h"
#include "editor/editor_settings.h"
#include "editor/editor_undo_redo_manager.h"

#include "editor/editor_log.h"
#include "editor/editor_node.h"

PGB_GizmoBox::PGB_GizmoBox() {
	helper.instantiate();
	const Color gizmo_color = SceneTree::get_singleton()->get_debug_collisions_color();
	create_material("shape_material", gizmo_color);
	create_handle_material("handles");

	//version_btn->connect(SceneStringName(pressed), callable_mp(this, &PGB_GizmoBox::update_gizmos));
	
	//InspectorDock::get_inspector_singleton()->connect("property_edited", callable_mp(this, &PGB_GizmoBox::update_gizmos));
}

PGB_GizmoBox::~PGB_GizmoBox() {
}

//void PGB_GizmoBox::update_gizmos() {
//	InspectorDock::get_inspector_singleton()->connect("property_edited", )
//}

bool PGB_GizmoBox::has_gizmo(Node3D *p_spatial) {
	return Object::cast_to<PGB_Box>(p_spatial) != nullptr;
}

String PGB_GizmoBox::get_gizmo_name() const {
	return "PGB_Box";
}

int PGB_GizmoBox::get_priority() const {
	return -1;
}

String PGB_GizmoBox::get_handle_name(const EditorNode3DGizmo *p_gizmo, int p_id, bool p_secondary) const {
	return helper->box_get_handle_name(p_id);
}

Variant PGB_GizmoBox::get_handle_value(const EditorNode3DGizmo *p_gizmo, int p_id, bool p_secondary) const {
	PGB_Box *cs = Object::cast_to<PGB_Box>(p_gizmo->get_node_3d());

	if (cs)
		return cs->get_size();
	return Variant();
}

void PGB_GizmoBox::begin_handle_action(const EditorNode3DGizmo *p_gizmo, int p_id, bool p_secondary) {
	helper->initialize_handle_action(get_handle_value(p_gizmo, p_id, p_secondary), p_gizmo->get_node_3d()->get_global_transform());
}

void PGB_GizmoBox::set_handle(const EditorNode3DGizmo *p_gizmo, int p_id, bool p_secondary, Camera3D *p_camera, const Point2 &p_point) {
	PGB_Box *box = Object::cast_to<PGB_Box>(p_gizmo->get_node_3d());

	Vector3 sg[2];
	helper->get_segment(p_camera, p_point, sg);

	Vector3 size = box->get_size();
	Vector3 position;
	helper->box_set_handle(sg, p_id, size, position);
	box->set_size(size);
	box->set_global_position(position);

	// Added to allow refresh at each value change. Calls PGB_GizmoBox::redraw() down the line.
	// https://github.com/godotengine/godot/issues/71979
	//box->update_gizmos();
}

void PGB_GizmoBox::commit_handle(const EditorNode3DGizmo *p_gizmo, int p_id, bool p_secondary, const Variant &p_restore, bool p_cancel) {
	PGB_Box *box = Object::cast_to<PGB_Box>(p_gizmo->get_node_3d());
	helper->box_commit_handle(TTR("Change Box Shape Size"), p_cancel, box, box);
}

void PGB_GizmoBox::redraw(EditorNode3DGizmo *p_gizmo) {
	PGB_Box *box = Object::cast_to<PGB_Box>(p_gizmo->get_node_3d());

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

	const Vector<Vector3> handles = helper->box_get_handles(box->get_size());

	p_gizmo->add_lines(lines, material);
	p_gizmo->add_collision_segments(lines);
	p_gizmo->add_handles(handles, handles_material);
}
