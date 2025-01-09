#ifndef PG_INPUT_H
#define PG_INPUT_H

#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "scene/main/node.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


// DOC: Has to inherit from Node because we need the input() method.


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class Array;
class ConfigFile;
enum class Key;
class InputEvent;
class StringName;

template <typename T>
class Vector;

template <typename K, typename V>
class VMap;

class PG_FS;
class PG_Msgr;
class PG_Profile;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


struct PG_InputBind {
	StringName device;
	Key key;

	PG_InputBind();
	PG_InputBind(StringName n_device, Key n_key);
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


struct PG_InputParams {
	bool mouse_vis;

	PG_InputParams();
	PG_InputParams(bool _mouse_vis);
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Input : public Node {
	GDCLASS(PG_Input, Node);
	PG_BIND;


//////////////////////////////////////////////////


protected:
	Ref<PG_Msgr> _msgr;

	Ref<PG_FS> _fs;

	Ref<PG_Profile> _prf;


//////////////////////////////////////////////////


protected:
	Ref<ConfigFile> _file;


//////////////////////////////////////////////////


protected:
	VMap<StringName, Vector<PG_InputBind>> _binds;

	VMap<StringName, Vector<StringName>> _actions;

	VMap<StringName, PG_InputParams> _params;

	Vector<StringName> _stack;


//////////////////////////////////////////////////


protected:
	void _set_actions();

	void _set_params();


//////////////////////////////////////////////////


protected:
	bool _file_disabled;

	bool _try_read_file_and_load_binds();

	bool _try_create_file();

	bool _read_file_and_load_binds();

	bool _write_file();


//////////////////////////////////////////////////


protected:
	Vector<Key> _get_keycodes(StringName act);

	void _add_to_binds(StringName act, StringName dev, Key k);

	void _set_custom_binds();


//////////////////////////////////////////////////


protected:
	void _set_default_binds();


//////////////////////////////////////////////////


protected:
	Array _get_keys_as_vec(Vector<PG_InputBind> v);

	void _filter_out_invalid_binds();


//////////////////////////////////////////////////


protected:
	void _load_keybind_set(StringName new_set);

	void _unload_keybind_set(StringName cur_set = "");

	void _clear_system_input_map();


//////////////////////////////////////////////////


public:
	bool get_cursor_visible();

	void set_cursor_visible(bool v);


//////////////////////////////////////////////////


public:
	virtual void input(const Ref<InputEvent> &e) override;


//////////////////////////////////////////////////


public:
	static PG_Input *mk(Ref<PG_Msgr> msgr, Ref<PG_FS> fs, Ref<PG_Profile> prf);


protected:
	PG_Input();
	PG_Input(Ref<PG_Msgr> msgr, Ref<PG_FS> fs, Ref<PG_Profile> prf);


public:
	~PG_Input();
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_INPUT_H
