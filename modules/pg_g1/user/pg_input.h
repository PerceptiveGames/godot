#ifndef PG_INPUT_H
#define PG_INPUT_H

#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "core/templates/vmap.h"
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


class PG_InputBind : public RefCounted {
	GDCLASS(PG_InputBind, RefCounted);


//////////////////////////////////////////////////


	template <typename T>
	friend class Ref;


//////////////////////////////////////////////////


protected:
	StringName _device;
	Key _key;


public:
	StringName get_device();
	Key get_key();


//////////////////////////////////////////////////


protected:
	PG_InputBind();


public:
	PG_InputBind(StringName device, Key key);
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_InputParams : public RefCounted {
	GDCLASS(PG_InputParams, RefCounted);
	

//////////////////////////////////////////////////


	template <typename T>
	friend class Ref;


//////////////////////////////////////////////////


protected:
	bool _mouse_vis;


public:
	bool get_mouse_vis();


//////////////////////////////////////////////////


protected:
	PG_InputParams();


public:
	PG_InputParams(bool mouse_vis);
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
	VMap<StringName, Vector<Ref<PG_InputBind>>> _binds;

	VMap<StringName, Vector<StringName>> _actions;

	VMap<StringName, Ref<PG_InputParams>> _params;

	Vector<StringName> _stack;


//////////////////////////////////////////////////


protected:
	void _set_actions();

	void _set_params();


//////////////////////////////////////////////////


protected:
	bool _cfg_disabled;

	Ref<ConfigFile> _try_load_cfg();

	Ref<ConfigFile> _try_mk_file();

	Ref<ConfigFile> _load_cfg();

	bool _write_file(Ref<ConfigFile> cfg);


//////////////////////////////////////////////////


protected:
	Vector<Key> _get_keycodes(Ref<ConfigFile> cfg, StringName act);

	void _add_to_binds(StringName act, StringName dev, Key k);

	bool _add_custom_keybinds(Ref<ConfigFile> cfg);


//////////////////////////////////////////////////


protected:
	void _set_default_keybinds();


//////////////////////////////////////////////////


protected:
	Array _get_keys_as_arr(Vector<Ref<PG_InputBind>> v);

	void _cleanup_cfg(Ref<ConfigFile> cfg);


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
