#include "core/error/error_list.h"
#include "core/input/input.h"
#include "core/input/input_event.h"
#include "core/input/input_map.h"
#include "core/io/config_file.h"
#include "core/io/file_access.h"
#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "core/os/keyboard.h"
#include "core/os/memory.h"
#include "core/string/string_name.h"
#include "core/string/ustring.h"
#include "core/templates/list.h"
#include "core/templates/vector.h"
#include "core/templates/vmap.h"
#include "core/variant/array.h"
#include "core/variant/typed_dictionary.h"
#include "core/variant/variant.h"
#include "modules/pg_g1/core/pg_fs.h"
#include "modules/pg_g1/core/pg_msgr.h"
#include "modules/pg_g1/core/pg_scene_tree.h"
#include "modules/pg_g1/data/pg_const.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/data/pg_paths.h"
#include "modules/pg_g1/exts/pg_arr.h"
#include "modules/pg_g1/exts/pg_num.h"
#include "modules/pg_g1/exts/pg_sn.h" // DOC: Used by template instantiation.
#include "modules/pg_g1/exts/pg_str.h"
#include "modules/pg_g1/exts/pg_vec.h"
#include "modules/pg_g1/sgns/pg_sgns_user.h"
#include "modules/pg_g1/types/pg_types.h"
#include "modules/pg_g1/types/pgw.h"
#include "modules/pg_g1/user/pg_input.h"
#include "modules/pg_g1/user/pg_profile.h"
#include "scene/main/viewport.h"
#include <initializer_list>



//////////////////////////////////////////////////
//////////////////////////////////////////////////


// TODO: Rename methods.


//#DOC : Loads custom values.
//#DOC : The.cfg file may not contain custom values for EVERY keybind.
//#NOTE : Deletes any binds not used in the game(could be a bind that was renamed by dev)
//#NOTE : Resaves the.cfg file with only existing and valid keybinds.
//#TODO : Manage the read - only case
//#TODO : Execute func after profile creation / selection
//#Very first possible input should be skipping intros / profile selection(with kb too)
//#TODO : Open file manually and add comment in header that it may be overwritten, if not already present.
//#Add comment that user should create custom_input.cfg file instead.
//#TODO : Actually manage a custom_input.cfg file.
//#TODO : Add warning if file is read - only.Tell of option to add to file to skip warning, e.g.'skip_readonly_warning = 1'
//#TODO : Don 't crash if failure to read or write config files. Just issue very visible warning that config and possibly saves won' t be saved.
//#TODO : Add console + screen warning when a bind is invalid.
//#TODO: Add signal that executes when config changes are validated(i.e.OK button clicked)



//////////////////////////////////////////////////
//////////////////////////////////////////////////


template<> int PG_Vec::resize_until_item<StringName>(Vector<StringName> &v, const StringName &item, bool pop_found_item);
extern template int PG_Vec::resize_until_item<StringName>(Vector<StringName> &v, const StringName &item, bool pop_found_item);


//////////////////////////////////////////////////
//////////////////////////////////////////////////


void PG_Input::_set_actions() {
	_actions["bindable"] = { "move_forward", "move_backwards", "move_left", "move_right", "jump", "crouch", "prone", "interact", "console_show",
		"menu_up", "menu_down", "menu_left", "menu_right", "menu_validate", "menu_cancel", "menu_reset",
		"console_hide", "console_history_prev", "console_history_next" };
	_actions["game"] = { "move_forward", "move_backwards", "move_left", "move_right", "jump", "crouch", "prone", "interact", "console_show" };
	_actions["main_menu"] = { "menu_up", "menu_down", "menu_left", "menu_right", "menu_validate", "menu_cancel", "menu_reset", "console_show" };
	_actions["pause_menu"] = { "menu_up", "menu_down", "menu_left", "menu_right", "menu_validate", "menu_cancel", "menu_reset", "console_show" };
	_actions["console"] = { "console_hide", "console_history_prev", "console_history_next" };
}


void PG_Input::_set_params() {
	_params["game"] = PG_InputParams(false);
	_params["main_menu"] = PG_InputParams(true);
	_params["pause_menu"] = PG_InputParams(true);
	_params["console"] = PG_InputParams(true);
}


//////////////////////////////////////////////////


bool PG_Input::_try_read_file_and_load_binds() {
	if (_file_disabled) { //  TODO: Remove if not needed.
		return false;
	}
	_st_(Ref<PGW_Str> fp = PG_Paths::input_file_path(_prf->get_id()));
	if (fp->nok()) {
		return false;
	}
	Error e = _file->load(fp->r());
	if (e) {
		if (FileAccess::exists(fp->r())) {
			_st_(_msgr->bcast(PGE_MsgLevel::ERROR, "INPUT_CFG_PARSE", e, PG_Str::mk_ta_str(fp->r())));
		}
		return false;
	}
	int ver = PG_Num::to_int_if_bw(_file->get_value("meta", "parser_version", -1), 1, pg_config_file_parser_version);
	if (ver < 0) {
		_st_(_msgr->bcast(PGE_MsgLevel::ERROR, "INPUT_PARSER_VER", fp->r()));
		return false;
	}
	// ....
	return true;
}


bool PG_Input::_try_create_file() {
	_st_(Ref<PGW_Str> fp = PG_Paths::input_file_path(_prf->get_id()));
	if (fp->nok()) {
		return false;
	}
	if (FileAccess::exists(fp->r())) {
		String nn = PG_Paths::add_ts_sfx(fp->r());
		_st_(_msgr->bcast(PGE_MsgLevel::WARNING_VIP, "INPUT_CFG_RN_OR_RM", PG_Str::mk_ta_str(fp->r(), nn, fp->r())));
		_if_st_(!_fs->rn_or_rm(fp->r(), nn)) {
			return false;
		}
	}
	_if_st_(!_fs->create_file_if_none(fp->r())) {
		return false;
	}
	Error e = _file->load(fp->r());
	if (e) {
		_st_(_msgr->bcast(PGE_MsgLevel::ERROR, "INPUT_CFG_LOAD", e, fp->r()));
		return false;
	}
	return true;
}


bool PG_Input::_read_file_and_load_binds() {
	_if_st_(!_try_read_file_and_load_binds() && !_try_create_file()) {
		_st_(_msgr->bcast(PGE_MsgLevel::ERROR, "INPUT_CFG_DISABLED"));
		return false;
	}
	return true;
}


bool PG_Input::_write_file() {
	_st_(Ref<PGW_Str> fp = PG_Paths::input_file_path(_prf->get_id()));
	Error e;
	if (fp->ok()) {
		e = _file->save(fp->r());
		if (!e) {
			return true;
		}
	}
	_st_(_msgr->bcast(PGE_MsgLevel::ERROR, "INPUT_CFG_SAVE", fp->r()));
	_st_(_msgr->bcast(PGE_MsgLevel::ERROR, "INPUT_CFG_DISABLED"));
	return false;
}


//////////////////////////////////////////////////


Vector<Key> PG_Input::_get_keycodes(StringName act) {
	Variant v = _file->get_value("keyboard", act, false);
	if (!v) {
		return Vector<Key>();
	}
	return PG_Vec::to_arr_of_valid_keycodes(v);
}


void PG_Input::_add_to_binds(StringName act, StringName dev, Key k) {
	if (!_binds.has(act)) {
		_binds[act] = Vector<PG_InputBind>();
	}
	_binds[act].append(PG_InputBind(dev, k));
}


void PG_Input::_set_custom_binds() {
	// DOC: Default value case already handled previously.
	// TODO: Do something with it.
	int ver = PG_Num::to_int(_file->get_value("meta", "parser_version", -1));

	for (StringName act : _actions["bindable"]) {
		for (Key k : _get_keycodes(act)) {
			_add_to_binds(act, "keyboard", k);
		}
	}
	// TODO: Add mouse binds. Later gamepad.
}


//////////////////////////////////////////////////


// DOC: Run this after reading and parsing from config file.
void PG_Input::_set_default_binds() {
	VMap<StringName, Key> kb;

	kb["menu_up"] = Key::UP;
	kb["menu_down"] = Key::DOWN;
	kb["menu_left"] = Key::LEFT;
	kb["menu_right"] = Key::RIGHT;
	kb["menu_validate"] = Key::ENTER;
	kb["menu_cancel"] = Key::ESCAPE;
	kb["menu_reset"] = Key::BACKSPACE;

	kb["move_forward"] = Key::W;
	kb["move_backwards"] = Key::S;
	kb["move_left"] = Key::A;
	kb["move_right"] = Key::D;
	kb["jump"] = Key::SPACE;
	kb["crouch"] = Key::SHIFT;
	kb["prone"] = Key::ALT;
	kb["interact"] = Key::E;

	kb["console_toggle"] = Key::F1;
	kb["console_history_prev"] = Key::UP;
	kb["console_history_next"] = Key::DOWN;

	for (int i = 0; i < kb.size(); ++i) {
		//if (!_binds.has(kv.key)) {
		_binds[kb.getk(i)] = { PG_InputBind("keyboard", kb.getv(i)) };
		//}
	}
}


//////////////////////////////////////////////////

Array PG_Input::_get_keys_as_vec(Vector<PG_InputBind> v) {
	Array r;
	for (PG_InputBind b : v) {
		r.append(b.key);
	}
	return r;
}



void PG_Input::_filter_out_invalid_binds() {
	_file->clear();
	// TODO: If parser version ever gets upgraded, do not forget data conversion.
	_file->set_value("meta", "parser_version", pg_config_file_parser_version);
	for (int i = 0; i < _binds.size(); ++i) {
		_file->set_value("keyboard", _binds.getk(i), _get_keys_as_vec(_binds.getv(i)));
	}
}


//////////////////////////////////////////////////


void PG_Input::_load_keybind_set(StringName new_set) {
	Vector<StringName> as = _actions[new_set];
	for (StringName a : as) {
		PG_S(InputMap)->add_action(a); // TODO: add optional deadzone
		for (PG_InputBind b : _binds[a]) {
			if (b.device == "keyboard") {
				Ref<InputEventKey> e = PG_Types::mk_ref<InputEventKey>();
				e->set_key_label(b.key);
				PG_S(InputMap)->action_add_event(a, e);
			}
		}
	}
	set_cursor_visible(_params[new_set].mouse_vis);
	PG_Vec::resize_until_item(_stack, new_set, true);
	_stack.append(new_set);
}


// DOC: 'cur_set' arg is an optional safety mechanism.
// If current_set is set, makes sure it matches the active keybind set.
void PG_Input::_unload_keybind_set(StringName cur_set) {
	StringName back_set = PG_Vec::pop_back(_stack);
	if (!cur_set.is_empty() && back_set != cur_set) {
		_st_(_msgr->bcast(PGE_MsgLevel::ERROR, "INPUT_WRONG_UNLOAD", PG_Str::mk_ta_str(back_set, cur_set)));
	}
	StringName new_set = PG_Vec::last(_stack);
	if (new_set == "") {
		_st_(_msgr->bcast(PGE_MsgLevel::ERROR, "INPUT_NO_SET"));
	} else {
		_load_keybind_set(new_set);
	}
}


void PG_Input::_clear_system_input_map() {
	// TODO : Eventually, just remove all custom InputMap entries in Project Settings
	// TODO : and use 'InputMap.load_from_project_settings()'.
	// TODO : This way, only the "ui_*" actions will remain.
	for (StringName a : PG_S(InputMap)->get_actions()) {
		if (!String(a).begins_with("ui_")) {
			PG_S(InputMap)->erase_action(a);
		}
	}
}


//////////////////////////////////////////////////


void PG_Input::set_cursor_visible(bool v) {
	PG_S(Input)->set_mouse_mode(v ? Input::MOUSE_MODE_VISIBLE : Input::MOUSE_MODE_CAPTURED);
}


bool PG_Input::get_cursor_visible() {
	return (PG_S(Input)->get_mouse_mode() == Input::MOUSE_MODE_VISIBLE ||
			PG_S(Input)->get_mouse_mode() == Input::MOUSE_MODE_CONFINED);
}


//////////////////////////////////////////////////


void PG_Input::input(const Ref<InputEvent> &e) {
	if (e->is_action_pressed("console_show")) {
		PG_I(PG_SgnsUser)->emit_signal("console_show_pressed");
		get_viewport()->set_input_as_handled();
		// TODO: Add "show pause menu", etc.. here
	}
}


//////////////////////////////////////////////////


#ifdef PG_GD_FNS
void PG_Input::_bind_methods() {
	//ADD_SIGNAL(MethodInfo("console_show_pressed"));
}
#endif


PG_Input *PG_Input::mk(Ref<PG_Msgr> msgr, Ref<PG_FS> fs, Ref<PG_Profile> prf) {
	return memnew(PG_Input(msgr, fs, prf));
		//pg_mk_ref<PG_Input>(msgr);
}


PG_Input::PG_Input() :
	_file_disabled(true) {}


PG_Input::PG_Input(Ref<PG_Msgr> msgr, Ref<PG_FS> fs, Ref<PG_Profile> prf) {
	_msgr = msgr;
	_fs = fs;
	_prf = prf;
	_set_actions();
	_set_params();
	_if_st_(_read_file_and_load_binds()) {
		_set_custom_binds();
	}
	List<String> ks;
	if (_file->has_section("keyboard")) {
		_file->get_section_keys("keyboard", &ks);
	}
	if (ks.size() == 0) {
		// DOC: Default binds are added only if config file is empty
		// or had only invalid entries in the "keyboard" section.
		_set_default_binds();
	}

	_file->clear();
	_filter_out_invalid_binds();

	_st_(_write_file());

	_clear_system_input_map();
	_load_keybind_set("game"); // TODO: TEMP.
}


PG_Input::~PG_Input() {}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
