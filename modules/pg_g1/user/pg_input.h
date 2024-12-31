#ifndef PG_INPUT_H
#define PG_INPUT_H

#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "core/os/keyboard.h"
#include "core/templates/vmap.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/types/pg_typedefs.h"
#include "scene/main/node.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


// DOC: Has to inherit from Node because we need the input() method.


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_FS;
class PG_Msgr;
class PG_Profile;

class ConfigFile;
class InputEvent;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


struct PG_InputBind {
	SN device;
	Key key;


	PG_InputBind() :
			device(SN()),
			key(Key::NONE) {}


	PG_InputBind(SN n_device, Key n_key) :
			device(n_device),
			key(n_key) {}
};


struct PG_InputParams {
	bool mouse_vis;


	PG_InputParams() : mouse_vis(false) {}


	PG_InputParams(bool _mouse_vis) {
		mouse_vis = _mouse_vis;
	}
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
	VMap<SN, Vec<PG_InputBind>> _binds;

	VMap<SN, SNV> _actions;

	VMap<SN, PG_InputParams> _params;

	SNV _stack;


//////////////////////////////////////////////////


protected:
	bool _file_disabled;

	bool _try_read_file_and_load_binds();

	bool _try_create_file();

	Vec<Key> _get_keycodes(SN act);

	void _add_to_binds(SN act, SN dev, Key k);

	bool _read_file_and_load_binds();

	Arr _get_keys_as_vec(Vec<PG_InputBind> v);

	void _filter_out_invalid_binds();

	bool _write_file();

	void _set_custom_binds();


//////////////////////////////////////////////////


protected:
	void _set_default_binds();


//////////////////////////////////////////////////


protected:
	void _set_actions();

	void _set_params();


//////////////////////////////////////////////////


public:
	virtual void input(const Ref<InputEvent> &e) override;


//////////////////////////////////////////////////


protected:
	void _load_keybind_set(SN new_set);

	void _unload_keybind_set(SN cur_set = "");

	void _clear_system_input_map();


//////////////////////////////////////////////////


public:
	bool get_cursor_visible();

	void set_cursor_visible(bool v);


//////////////////////////////////////////////////


public:
	static PG_Input *mk(Ref<PG_Msgr> msgr, Ref<PG_FS> fs, Ref<PG_Profile> prf);

	PG_Input();
	PG_Input(Ref<PG_Msgr> msgr, Ref<PG_FS> fs, Ref<PG_Profile> prf);
	~PG_Input();
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_INPUT_H
