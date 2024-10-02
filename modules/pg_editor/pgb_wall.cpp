/**************************************************************************/
/*  pgb_wall.cpp                                                          */
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

#include "PGB_Wall.h"

//void PGWall::reconstruct() {
//
//	TypedArray<Node> arr;
//	int cc = get_child_count(false);
//	//arr.resize(cc);
//	for (int i = 0; i < cc; i++) {
//		Node* child = get_child(i, false);
//		if (Object::cast_to<PGBoxCavity3D>(child))
//			continue;
//		child->queue_free();
//		EditorNode::get_log()->add_message("DELETING CHILD", EditorLog::MSG_TYPE_ERROR);
//	}
//}

PGB_Wall::PGB_Wall() :
		PGB_Box() {
}

PGB_Wall::~PGB_Wall() {
}

PGB_WallCavity::PGB_WallCavity() :
		PGB_Box() {
}

PGB_WallCavity::~PGB_WallCavity() {
}
