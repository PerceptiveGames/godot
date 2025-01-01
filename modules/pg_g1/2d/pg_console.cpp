#include "core/error/error_list.h"
#include "core/input/input_event.h"
#include "core/object/callable_method_pointer.h"
#include "core/object/class_db.h"
#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "core/typedefs.h"
#include "modules/pg_g1/2d/pg_console.h"
#include "modules/pg_g1/core/pg_cmds.h"
#include "modules/pg_g1/core/pg_msgr.h"
#include "modules/pg_g1/core/pg_scene_tree.h"
#include "modules/pg_g1/core/pg_timers.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/exts/pg_str.h"
#include "modules/pg_g1/exts/pg_vec.h"
#include "modules/pg_g1/sgns/pg_sgns_user.h"
#include "modules/pg_g1/types/pg_typedefs.h"
#include "scene/gui/line_edit.h"
#include "scene/gui/rich_text_label.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


void PG_Console::_show_console() {
	if (is_visible()) {
		return;
	}
	set_visible(true);
	// TODO: Add load binds here.
	set_process_input(true);
	_input->grab_focus();
	//visibility_toggled.emit(true)
}


void PG_Console::_hide_console() {
	if (!is_visible()) {
		return;
	}
	set_visible(false);
	// TODO: Add unload binds here.
	set_process_input(false);
	//visibility_toggled.emit(false)
}


void PG_Console::_show_history_prev() {
	if (!_input->has_focus() || _history.is_empty()) {
		return;
	}
	_history_idx = MAX(0, _history_idx - 1);
	_input->set_text(_history[_history_idx]);
	// DOC: Prevents cursor from moving to start of line bc of pressing KEY_UP.
	// TODO: Instead of the following call, either try to disable default KEY_UP shortcut,
	// or try to use '_input->set_deferred' to set caret to end.
	_timers->deferred_one_shot(this, callable_mp(this, &PG_Console::_set_caret_to_end));
}
 

void PG_Console::_show_history_next() {
	if (!_input->has_focus() || _history.is_empty()) {
		return;
	}
	_history_idx = MIN(_history.size() - 1, _history_idx + 1);
	_input->set_text(_history[_history_idx]);
	//_set_caret_to_end();
}


void PG_Console::_set_caret_to_end() {
	_input->set_caret_column(_input->get_text().length());
}


//////////////////////////////////////////////////


void PG_Console::input(const Ref<InputEvent> &e) {
	if (e->is_action_pressed("console_hide")) {
		get_viewport()->set_input_as_handled();
		_hide_console();
	} else if (e->is_action_pressed("console_history_prev")) {
		get_viewport()->set_input_as_handled();
		_show_history_prev();
	} else if (e->is_action_pressed("console_history_next")) {
		get_viewport()->set_input_as_handled();
		_show_history_next();
	}
}


void PG_Console::_text_submitted(Str t) {
	t = PG_Str::rm_rpt_chars(t, " ", true);
	if (t.is_empty()) {
		return;
	}

	// _on_input_text_changed
	PG_Vec::rm_adj_dupes(_history);
	_history.append("");
	_history_idx = _history.size() - 1;
	_input->set_text("");

	_st_(_msgr->bcast(PGE_MsgLevel::INPUT, SNV(), t, Error::OK, TA<Str>()));

	_cmds->send(t);
}


//////////////////////////////////////////////////


#ifdef PG_GD_FNS
void PG_Console::_bind_methods() {
	ClassDB::bind_method(D_METHOD("show_console"), &PG_Console::_show_console);
	ClassDB::bind_method(D_METHOD("hide_console"), &PG_Console::_hide_console);
	ClassDB::bind_method(D_METHOD("show_history_prev"), &PG_Console::_show_history_prev);
	ClassDB::bind_method(D_METHOD("show_history_next"), &PG_Console::_show_history_next);
	ClassDB::bind_method(D_METHOD("set_caret_to_end"), &PG_Console::_set_caret_to_end);
}
#endif


PG_Console::PG_Console(Ref<PG_Msgr> msgr, Ref<PG_Timers> timers, Ref<PG_Cmds> cmds) {
	_msgr = msgr;
	_timers = timers;
	_cmds = cmds;

	set_process_input(false);

	PG_I(PG_SgnsUser)->connect("console_show_pressed", callable_mp(this, &PG_Console::_show_console));

	//_output->set_unique_name_in_owner(true);
	//_input->set_unique_name_in_owner(true);
	_output = Object::cast_to<RichTextLabel>(find_child("Output"));
	_input = Object::cast_to<LineEdit>(find_child("Input"));

	_input->connect("text_submitted", callable_mp(this, &PG_Console::_text_submitted));
}


PG_Console::~PG_Console() {
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
