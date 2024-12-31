/**************************************************************************/
/*  pgn_resizable_box.cpp                                                 */
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


#include "pgn_resizable_box.h"


void PGN_ResizableBox::set_size(const Vector3 &p_size) {
	size = p_size;
	update_gizmos();
}

void PGN_ResizableBox::_set_size_in_inspector(const Vector3 &p_size) {
	size = p_size;
	// TODO: order of the two following calls?
	emit_signal("size_set_in_inspector");
	update_gizmos();
}

Vector3 PGN_ResizableBox::get_size() const {
	return size;
}


// TODO: Is this local position always size / 2?
Vector3 PGN_ResizableBox::get_ctr_pos() {
	return size / 2;
}

Vector3 PGN_ResizableBox::get_ctr_gpos() {
	return to_global(get_ctr_pos());
}


Vector3 PGN_ResizableBox::get_frnctr_pos() {
	return Vector3(size.x / 2, size.y / 2, size.z);
}

Vector3 PGN_ResizableBox::get_frnctr_gpos() {
	return to_global(get_frnctr_pos());
}

Vector3 PGN_ResizableBox::get_frn_nrm() {
	return Vector3(0, 0, 1);
}

Vector3 PGN_ResizableBox::get_frn_gnrm() {
	return to_global(Vector3(0, 0, 1));
}


Vector3 PGN_ResizableBox::get_bckctr_pos() {
	return Vector3(size.x / 2, size.y / 2, 0);
}

Vector3 PGN_ResizableBox::get_bckctr_gpos() {
	return to_global(get_bckctr_pos());
}

Vector3 PGN_ResizableBox::get_bck_nrm() {
	return Vector3(0, 0, -1);
}

Vector3 PGN_ResizableBox::get_bck_gnrm() {
	return to_global(Vector3(0, 0, -1));
}


Vector3 PGN_ResizableBox::get_lefctr_pos() {
	return Vector3(0, size.y / 2, size.z / 2);
}

Vector3 PGN_ResizableBox::get_lefctr_gpos() {
	return to_global(get_lefctr_pos());
}

Vector3 PGN_ResizableBox::get_lef_nrm() {
	return Vector3(-1, 0, 0);
}

Vector3 PGN_ResizableBox::get_lef_gnrm() {
	return to_global(Vector3(-1, 0, 0));
}


Vector3 PGN_ResizableBox::get_rigctr_pos() {
	return Vector3(size.x, size.y / 2, size.z / 2);
}

Vector3 PGN_ResizableBox::get_rigctr_gpos() {
	return to_global(get_rigctr_pos());
}

Vector3 PGN_ResizableBox::get_rig_nrm() {
	return Vector3(1, 0, 0);
}

Vector3 PGN_ResizableBox::get_rig_gnrm() {
	return to_global(Vector3(1, 0, 0));
}


Vector3 PGN_ResizableBox::get_botctr_pos() {
	return Vector3(size.x / 2, 0, size.z / 2);
}

Vector3 PGN_ResizableBox::get_botctr_gpos() {
	return to_global(get_botctr_pos());
}

Vector3 PGN_ResizableBox::get_bot_nrm() {
	return Vector3(0, -1, 0);
}

Vector3 PGN_ResizableBox::get_bot_gnrm() {
	return to_global(Vector3(0, -1, 0));
}


Vector3 PGN_ResizableBox::get_topctr_pos() {
	return Vector3(size.x / 2, size.y, size.z / 2);
}

Vector3 PGN_ResizableBox::get_topctr_gpos() {
	return to_global(get_topctr_pos());
}

Vector3 PGN_ResizableBox::get_top_nrm() {
	return Vector3(0, 1, 0);
}

Vector3 PGN_ResizableBox::get_top_gnrm() {
	return to_global(Vector3(0, 1, 0));
}


void PGN_ResizableBox::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_size", "size"), &PGN_ResizableBox::set_size);
	ClassDB::bind_method(D_METHOD("_set_size_in_inspector", "size"), &PGN_ResizableBox::_set_size_in_inspector);
	ClassDB::bind_method(D_METHOD("get_size"), &PGN_ResizableBox::get_size);

	ClassDB::bind_method(D_METHOD("get_ctr_pos"), &PGN_ResizableBox::get_ctr_pos);
	ClassDB::bind_method(D_METHOD("get_ctr_gpos"), &PGN_ResizableBox::get_ctr_gpos);

	ClassDB::bind_method(D_METHOD("get_frnctr_pos"), &PGN_ResizableBox::get_frnctr_pos);
	ClassDB::bind_method(D_METHOD("get_frnctr_gpos"), &PGN_ResizableBox::get_frnctr_gpos);
	ClassDB::bind_method(D_METHOD("get_frn_nrm"), &PGN_ResizableBox::get_frn_nrm);
	ClassDB::bind_method(D_METHOD("get_frn_gnrm"), &PGN_ResizableBox::get_frn_gnrm);

	ClassDB::bind_method(D_METHOD("get_bckctr_pos"), &PGN_ResizableBox::get_bckctr_pos);
	ClassDB::bind_method(D_METHOD("get_bckctr_gpos"), &PGN_ResizableBox::get_bckctr_gpos);
	ClassDB::bind_method(D_METHOD("get_bck_nrm"), &PGN_ResizableBox::get_bck_nrm);
	ClassDB::bind_method(D_METHOD("get_bck_gnrm"), &PGN_ResizableBox::get_bck_gnrm);

	ClassDB::bind_method(D_METHOD("get_lefctr_pos"), &PGN_ResizableBox::get_lefctr_pos);
	ClassDB::bind_method(D_METHOD("get_lefctr_gpos"), &PGN_ResizableBox::get_lefctr_gpos);
	ClassDB::bind_method(D_METHOD("get_lef_nrm"), &PGN_ResizableBox::get_lef_nrm);
	ClassDB::bind_method(D_METHOD("get_lef_gnrm"), &PGN_ResizableBox::get_lef_gnrm);

	ClassDB::bind_method(D_METHOD("get_rigctr_pos"), &PGN_ResizableBox::get_rigctr_pos);
	ClassDB::bind_method(D_METHOD("get_rigctr_gpos"), &PGN_ResizableBox::get_rigctr_gpos);
	ClassDB::bind_method(D_METHOD("get_rig_nrm"), &PGN_ResizableBox::get_rig_nrm);
	ClassDB::bind_method(D_METHOD("get_rig_gnrm"), &PGN_ResizableBox::get_rig_gnrm);

	ClassDB::bind_method(D_METHOD("get_botctr_pos"), &PGN_ResizableBox::get_botctr_pos);
	ClassDB::bind_method(D_METHOD("get_botctr_gpos"), &PGN_ResizableBox::get_botctr_gpos);
	ClassDB::bind_method(D_METHOD("get_bot_nrm"), &PGN_ResizableBox::get_bot_nrm);
	ClassDB::bind_method(D_METHOD("get_bot_gnrm"), &PGN_ResizableBox::get_bot_gnrm);

	ClassDB::bind_method(D_METHOD("get_topctr_pos"), &PGN_ResizableBox::get_topctr_pos);
	ClassDB::bind_method(D_METHOD("get_topctr_gpos"), &PGN_ResizableBox::get_topctr_gpos);
	ClassDB::bind_method(D_METHOD("get_top_nrm"), &PGN_ResizableBox::get_top_nrm);
	ClassDB::bind_method(D_METHOD("get_top_gnrm"), &PGN_ResizableBox::get_top_gnrm);

	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "size", PROPERTY_HINT_NONE, "suffix:m"), "_set_size_in_inspector", "get_size");

	ADD_SIGNAL(MethodInfo("begin_handle_moved"));
	ADD_SIGNAL(MethodInfo("handle_moved"));
	ADD_SIGNAL(MethodInfo("end_handle_moved"));
	ADD_SIGNAL(MethodInfo("size_set_in_inspector"));
}


PGN_ResizableBox::PGN_ResizableBox() {
}

PGN_ResizableBox::~PGN_ResizableBox() {
}
