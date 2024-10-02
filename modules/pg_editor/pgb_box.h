/**************************************************************************/
/*  pgb_box.h                                                             */
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

#ifndef PGB_BOX_H
#define PGB_BOX_H

#include "core/templates/local_vector.h"
#include "scene/3d/node_3d.h"

class PGB_Box: public Node3D {
	GDCLASS(PGB_Box, Node3D);

protected:
	AABB aabb;
	Vector3 size = Vector3(5, 5, 5);

public:
	void set_size(const Vector3 &p_size);
	Vector3 get_size() const;

protected:
	static void _bind_methods();

public:
	//Vector3 get_origin();

	//float get_length();
	//float get_height();
	//float get_depth();

	//float get_pos(StringName &pos);
	//float get_bot_pos();
	//float get_top_pos();
	//float get_left_pos();
	//float get_right_pos();
	//float get_near_pos();
	//float get_far_pos();
public:
	PGB_Box();
	~PGB_Box();
};

#endif // PGB_BOX_H
