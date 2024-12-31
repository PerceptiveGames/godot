/**************************************************************************/
/*  pgn_resizable_box.h                                                   */
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


#ifndef PGN_RESIZABLEBOX_H
#define PGN_RESIZABLEBOX_H

#include "scene/3d/node_3d.h"


struct Vector3;

class PGN_ResizableBox: public Node3D {
	GDCLASS(PGN_ResizableBox, Node3D);

protected:
	Vector3 size = Vector3(1, 1, 1);
	bool _has_x_handles = true;
	bool _has_y_handles = true;
	bool _has_z_handles = true;


public:
	void set_size(const Vector3 &p_size);
	void _set_size_in_inspector(const Vector3 &p_size);
	Vector3 get_size() const;

	Vector3 get_ctr_pos();
	Vector3 get_ctr_gpos();

	Vector3 get_frnctr_pos();
	Vector3 get_frnctr_gpos();
	Vector3 get_frn_nrm();
	Vector3 get_frn_gnrm();

	Vector3 get_bckctr_pos();
	Vector3 get_bckctr_gpos();
	Vector3 get_bck_nrm();
	Vector3 get_bck_gnrm();

	Vector3 get_lefctr_pos();
	Vector3 get_lefctr_gpos();
	Vector3 get_lef_nrm();
	Vector3 get_lef_gnrm();

	Vector3 get_rigctr_pos();
	Vector3 get_rigctr_gpos();
	Vector3 get_rig_nrm();
	Vector3 get_rig_gnrm();

	Vector3 get_botctr_pos();
	Vector3 get_botctr_gpos();
	Vector3 get_bot_nrm();
	Vector3 get_bot_gnrm();

	Vector3 get_topctr_pos();
	Vector3 get_topctr_gpos();
	Vector3 get_top_nrm();
	Vector3 get_top_gnrm();

	bool has_x_handles() const { return _has_x_handles; }
	bool has_y_handles() const { return _has_y_handles; }
	bool has_z_handles() const { return _has_z_handles; }


protected:
	static void _bind_methods();


public:
	PGN_ResizableBox();
	~PGN_ResizableBox();
};

#endif // PGN_RESIZABLEBOX_H
