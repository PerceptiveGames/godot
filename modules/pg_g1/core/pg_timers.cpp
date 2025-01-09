#include "core/object/callable_method_pointer.h"
#include "core/object/class_db.h"
#include "core/object/ref_counted.h"
#include "core/templates/vector.h"
#include "core/variant/callable.h"
#include "core/variant/variant.h"
#include "core/variant/variant_utility.h"
#include "modules/pg_g1/core/pg_msgr.h"
#include "modules/pg_g1/core/pg_scene_tree.h"
#include "modules/pg_g1/core/pg_time.h"
#include "modules/pg_g1/core/pg_timers.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/types/pg_types.h"
#include "scene/main/node.h"
#include <cmath>


//////////////////////////////////////////////////
//////////////////////////////////////////////////


// TODO: Remove 'init()' functions and put args in ctor instead.
// Only if default empty ctor is not needed when trying to run editor.
// TODO: Check in every file that .unref() is the way to go.
// TODO: If needed, add new pulse timer type
// where it is 'pulse_interval' and 'finish_f' that are defined.


//////////////////////////////////////////////////
//////////////////////////////////////////////////


Ref<PG_TimerUnit> PG_TimerUnit::_start(int pass_time, int pass_count, const Callable &pass_f, bool call_f_on_start, Variant time_scale_id) {
	_pass_time = pass_time;
	_pass_count = pass_count;
	_pass_f = pass_f;
	_time_scale_id = time_scale_id;

	_pass_time_left = pass_time;
	_pass_count_left = pass_count;

	if (call_f_on_start) {
		pass_f.call(0);
	}

	return this;
}


// DOC: Returns 'false' when we're at the last loop.
//Ref<PG_TimerUnit> PG_TimerUnit::_update(int delta) {
bool PG_TimerUnit::_update(PG_Time *time, int delta) {
	_pass_time_left -= VariantUtilityFunctions::roundi(delta * time->get_time_scale(_time_scale_id));
	if (_pass_time_left <= 0) {
		if (_pass_count_left > 0) {
			_pass_count_left--;
		}
		if (!_pass_f.is_null()) {
			_pass_f.call(float(_pass_count - _pass_count_left) / _pass_count); // DOC: Arg from 0 to 1.
		}
		if (_pass_count_left == 0) {
			// TODO: Check this.
			//return pg_unref(this);
			return false;
		}
		// DOC: Resets the countdown it takes for a pass.
		// Adds to current negative value instead of adding to 0 so as not to eat time after every loop.
		_pass_time_left += _pass_time;
	}
	//return this;
	return true;
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////


Ref<PG_Timer> PG_Timer::set_initial_delay(const float d) {
	_initial_delay = d;
	return this;
}


Ref<PG_Timer> PG_Timer::set_time_scale_id(const Variant &id) {
	_time_scale_id = id;
	return this;
}


Ref<PG_Timer> PG_Timer::set_process_mode(const Node::ProcessMode m) {
#if PG_BUILD_LEVEL < PG_RELEASE
	if (m == Node::PROCESS_MODE_INHERIT && !_process_mode_parent) {
		_st_(_msgr->bcast(PGE_MsgLevel::ERROR, "TIMER_INSTANCE_PROCESS_MODE", to_string()));
	}
#endif // PG_BUILD_LEVEL < PG_RELEASE

	_process_mode = m;
	return this;
}


bool PG_Timer::is_persistent() const {
	return _persistent;
}


//////////////////////////////////////////////////


void PG_Timer::start() {
	if (_has_started) {
		_st_(_msgr->bcast(PGE_MsgLevel::WARNING, "TIMER_STARTED_IN_START", to_string()));
	}
	if (_is_running) {
		_st_(_msgr->bcast(PGE_MsgLevel::WARNING, "TIMER_RUNNING_IN_START", to_string()));
	}
	if (_initial_delay) {
		_handle_delay.instantiate();
		_handle_delay->_start(_initial_delay, 1, Callable(), false, _time_scale_id);
	}
	if (_pulse_f.is_valid()) {
		_pulse_f.call();
		_handle_pulse.instantiate();
		_handle_pulse->_start(_pulse_interval, _pulse_count, _pulse_f, true, _time_scale_id);
	}
	if (_finish_f.is_valid()) {
		_handle_finish.instantiate();
		_handle_finish->_start(_finish_delay, 1, _finish_f, false, _time_scale_id);
	}

	_has_started = true;
	_is_running = true;
}


bool PG_Timer::pause() {
	if (_safeguard) {
		_st_(_msgr->bcast(PGE_MsgLevel::ERROR, "TIMER_F_CALL_IN_CALLBACK", to_string()));
		return false;
	}
	if (!_has_started) {
		_st_(_msgr->bcast(PGE_MsgLevel::WARNING, "TIMER_NOT_STARTED_IN_PAUSE", to_string()));
	}
	if (!_is_running) {
		_st_(_msgr->bcast(PGE_MsgLevel::WARNING, "TIMER_NOT_RUNNING_IN_PAUSE", to_string()));
	}
	_is_running = false;
	return true;
}


bool PG_Timer::resume() {
	if (_safeguard) {
		_st_(_msgr->bcast(PGE_MsgLevel::ERROR, "TIMER_F_CALL_IN_CALLBACK", to_string()));
		return false;
	}
	if (!_has_started) {
		_st_(_msgr->bcast(PGE_MsgLevel::WARNING, "TIMER_NOT_STARTED_IN_RESUME", to_string()));
	}
	if (_is_running) {
		_st_(_msgr->bcast(PGE_MsgLevel::WARNING, "TIMER_RUNNING_IN_RESUME", to_string()));
	}
	_is_running = true;
	return true;
}


bool PG_Timer::restart() {
	if (_safeguard) {
		_st_(_msgr->bcast(PGE_MsgLevel::ERROR, "TIMER_F_CALL_IN_CALLBACK", to_string()));
		return false;
	}
	if (!_has_started) {
		_st_(_msgr->bcast(PGE_MsgLevel::WARNING, "TIMER_NOT_STARTED_IN_RESTART", to_string()));
	}
	_st_(cancel());
	_st_(start());
	return true;
}


bool PG_Timer::cancel() {
	if (_safeguard) {
		_st_(_msgr->bcast(PGE_MsgLevel::ERROR, "TIMER_F_CALL_IN_CALLBACK", to_string()));
		return false;
	}
	if (!_has_started) {
		_st_(_msgr->bcast(PGE_MsgLevel::WARNING, "TIMER_NOT_STARTED_IN_CANCEL", to_string()));
	}
	if (_handle_pulse.is_valid()) {
		_handle_pulse.unref();
	}
	if (_handle_finish.is_valid()) {
		_handle_finish.unref();
	}
	_is_running = false;
	_has_started = false;
	return true;
}


//////////////////////////////////////////////////


// DOC: Returns 'false' when we're at the last loop.
bool PG_Timer::_update(PG_Time *time, int delta, bool paused) {
	if (!_is_running) {
		return true;
	}
	// DOC: Deletes timer if process_mode is inherit and parent node is not found.
	if (_inherits_null_node()) {
		return false;
	}
	if (!_gatekeep_by_process_mode(paused)) {
		return true;
	}
	if (_handle_delay.is_valid()) {
		_safeguard = true;
		bool r = _handle_delay->_update(time, delta);
		_safeguard = false;
		if (r) {
			return true;
		} else {
			// TODO: Correct?
			_handle_delay.unref();
		}
	}
	if (_handle_pulse.is_valid()) {
		_safeguard = true;
		bool r = _handle_pulse->_update(time, delta);
		_safeguard = false;
		if (r) {
			return true;
		} else {
			// TODO: Correct?
			_handle_pulse.unref();
		}
	}
	if (_handle_finish.is_valid()) {
		_safeguard = true;
		bool r = _handle_finish->_update(time, delta);
		_safeguard = false;
		// TODO: Correct?
		_handle_finish.unref();
	}
	_is_running = false;
	_has_started = false;
	return false;
}


Node::ProcessMode PG_Timer::_get_inherited_process_mode(const Node *node) const {
	while (node->get_process_mode() == Node::PROCESS_MODE_INHERIT) {
		node = node->get_parent();
	}
	return node->get_process_mode();
}


bool PG_Timer::_inherits_null_node() {
	return _process_mode == Node::PROCESS_MODE_INHERIT && !_process_mode_parent;
}


bool PG_Timer::_gatekeep_by_process_mode(bool paused) {
	Node::ProcessMode process_mode = _process_mode;
	if (process_mode == Node::PROCESS_MODE_INHERIT) {
		// DOC: By this point, '_process_mode_parent' is assumed to not be null.
		process_mode = _get_inherited_process_mode(_process_mode_parent);
	}
	if (process_mode == Node::PROCESS_MODE_DISABLED) {
		return false;
	}
	if (process_mode == Node::PROCESS_MODE_PAUSABLE && paused) {
		return false;
	}
	if (process_mode == Node::PROCESS_MODE_WHEN_PAUSED && !paused) {
		return false;
	}
	return true;
}


void PG_Timer::_setup_process_mode(Node *process_mode_parent) {
	if (process_mode_parent) {
		_process_mode_parent = process_mode_parent;
		_process_mode = Node::PROCESS_MODE_INHERIT;
	}
	// DOC: Else: Keeps default, which is 'PROCESS_MODE_PAUSABLE'.
}


//////////////////////////////////////////////////


void PG_Timer::_bind_methods() {
#ifdef PG_GD_FNS
	ClassDB::bind_method(D_METHOD("set_initial_delay", "d"), &PG_Timer::set_initial_delay);
	ClassDB::bind_method(D_METHOD("set_time_scale_id", "id"), &PG_Timer::set_time_scale_id);
	ClassDB::bind_method(D_METHOD("set_process_mode", "m"), &PG_Timer::set_process_mode);
	ClassDB::bind_method(D_METHOD("is_persistent"), &PG_Timer::is_persistent);

	ClassDB::bind_method(D_METHOD("start"), &PG_Timer::start);
	ClassDB::bind_method(D_METHOD("pause"), &PG_Timer::pause);
	ClassDB::bind_method(D_METHOD("resume"), &PG_Timer::resume);
	ClassDB::bind_method(D_METHOD("restart"), &PG_Timer::restart);
	ClassDB::bind_method(D_METHOD("cancel"), &PG_Timer::cancel);
#endif
}


PG_Timer::PG_Timer() {
	_pulse_interval = -1.0f;
	_pulse_count = -INFINITY;

	_finish_delay = -1.0f;

	_process_mode = Node::ProcessMode::PROCESS_MODE_PAUSABLE;
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////


Ref<PG_TimerSimple> PG_TimerSimple::init(Ref<PG_Msgr> msgr, Node *process_mode_parent, float finish_delay, const Callable &finish_f, bool persistent) {
	_msgr = msgr;
	_setup_process_mode(process_mode_parent);
	_finish_f = finish_f;
	_finish_delay = finish_delay;
	_persistent = persistent;
	return this;
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////


Ref<PG_TimerSimplePulse> PG_TimerSimplePulse::init(Ref<PG_Msgr> msgr, Node *process_mode_parent, int pulse_count, const Callable &pulse_f, float finish_delay, const Callable &finish_f, bool persistent) {
	_msgr = msgr;
	_setup_process_mode(process_mode_parent);
	_pulse_interval = finish_delay / pulse_count;
	_pulse_count = pulse_count;
	_pulse_f = pulse_f;
	_finish_f = finish_f;
	_finish_delay = finish_delay;
	_persistent = persistent;
	return this;
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////


Ref<PG_TimerPulse> PG_TimerPulse::init(Ref<PG_Msgr> msgr, Node *process_mode_parent, float pulse_interval, int pulse_count, const Callable &pulse_f, const Callable &finish_f, bool persistent) {
	_msgr = msgr;
	_setup_process_mode(process_mode_parent);
	_pulse_interval = pulse_interval;
	_pulse_count = pulse_count;
	_pulse_f = pulse_f;
	_finish_f = finish_f;
	_finish_delay = pulse_interval * pulse_count;
	_persistent = persistent;
	return this;
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////


Ref<PG_TimerInfinitePulse> PG_TimerInfinitePulse::init(Ref<PG_Msgr> msgr, Node *process_mode_parent, float pulse_interval, const Callable &pulse_f, bool persistent) {
	_msgr = msgr;
	_setup_process_mode(process_mode_parent);
	_pulse_interval = pulse_interval;
	_pulse_f = pulse_f;
	_persistent = persistent;
	return this;
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////


Ref<PG_TimerDeferredOneShot> PG_TimerDeferredOneShot::init(Ref<PG_Msgr> msgr, Node *process_mode_parent, const Callable &f) {
	_msgr = msgr;
	_setup_process_mode(process_mode_parent);
	_finish_f = f;
	_finish_delay = 0;
	_persistent = false;
	return this;
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////


Ref<PG_Timer> PG_Timers::_add(int grp, const Ref<PG_Timer> timer) {
	_timers.get(grp).append(timer);
	return timer;
}


//////////////////////////////////////////////////


Ref<PG_TimerSimple> PG_Timers::simple(Node *process_mode_parent, float finish_delay, const Callable &finish_f) {
	return _add(1, PG_Types::mk_ref<PG_TimerSimple>()->init(_msgr, process_mode_parent, finish_delay, finish_f, false));
}


Ref<PG_TimerSimplePulse> PG_Timers::simple_pulse(Node *process_mode_parent, int pulse_count, const Callable &pulse_f, float finish_delay, const Callable &finish_f) {
	return _add(1, PG_Types::mk_ref<PG_TimerSimplePulse>()->init(_msgr, process_mode_parent, pulse_count, pulse_f, finish_delay, finish_f, false));
}


Ref<PG_TimerPulse> PG_Timers::pulse(Node *process_mode_parent, float pulse_interval, int pulse_count, const Callable &pulse_f, const Callable &finish_f) {
	return _add(1, PG_Types::mk_ref<PG_TimerPulse>()->init(_msgr, process_mode_parent, pulse_interval, pulse_count, pulse_f, finish_f, false));
}


Ref<PG_TimerInfinitePulse> PG_Timers::infinite(Node *process_mode_parent, float pulse_interval, const Callable &pulse_f) {
	return _add(1, PG_Types::mk_ref<PG_TimerInfinitePulse>()->init(_msgr, process_mode_parent, pulse_interval, pulse_f, false));
}


Ref<PG_TimerSimple> PG_Timers::simple_persistent(Node *process_mode_parent, float finish_delay, const Callable &finish_f) {
	return _add(1, PG_Types::mk_ref<PG_TimerSimple>()->init(_msgr, process_mode_parent, finish_delay, finish_f, true));
}


Ref<PG_TimerSimplePulse> PG_Timers::simple_pulse_persistent(Node *process_mode_parent, int pulse_count, const Callable &pulse_f, float finish_delay, const Callable &finish_f) {
	return _add(1, PG_Types::mk_ref<PG_TimerSimplePulse>()->init(_msgr, process_mode_parent, pulse_count, pulse_f, finish_delay, finish_f, true));
}


Ref<PG_TimerPulse> PG_Timers::pulse_persistent(Node *process_mode_parent, float pulse_interval, int pulse_count, const Callable &pulse_f, const Callable &finish_f) {
	return _add(1, PG_Types::mk_ref<PG_TimerPulse>()->init(_msgr, process_mode_parent, pulse_interval, pulse_count, pulse_f, finish_f, true));
}


Ref<PG_TimerInfinitePulse> PG_Timers::infinite_persistent(Node *process_mode_parent, float pulse_interval, const Callable &pulse_f) {
	return _add(1, PG_Types::mk_ref<PG_TimerInfinitePulse>()->init(_msgr, process_mode_parent, pulse_interval, pulse_f, true));
}


Ref<PG_TimerDeferredOneShot> PG_Timers::deferred_one_shot(Node *process_mode_parent, const Callable &f) {
	return _add(0, PG_Types::mk_ref<PG_TimerDeferredOneShot>()->init(_msgr, process_mode_parent, f));
}


//////////////////////////////////////////////////


void PG_Timers::process(int delta) {
	bool paused = _stree->pg_is_paused();
	for (int i = 0; i < _timers.size(); i++) {
		for (int j = 0; j < _timers[i].size(); j++) {
			Ref<PG_Timer> timer = _timers[i][j];
			if (!timer->_update(_time, delta, paused)) {
				if (!timer->is_persistent()) {
					timer.unref();
					_timers.get(i).remove_at(j);
					j--;
				}
			}
		}
	}
}


//////////////////////////////////////////////////


void PG_Timers::_bind_methods() {
#ifdef PG_GD_FNS
	ClassDB::bind_method(D_METHOD("simple", "process_mode_parent", "finish_delay", "finish_f"), &PG_Timers::simple);
	ClassDB::bind_method(D_METHOD("simple_pulse", "process_mode_parent", "pulse_count", "pulse_f", "finish_delay", "finish_f"), &PG_Timers::simple_pulse);
	ClassDB::bind_method(D_METHOD("pulse", "process_mode_parent", "pulse_interval", "pulse_count", "pulse_f", "finish_f"), &PG_Timers::pulse);
	ClassDB::bind_method(D_METHOD("infinite", "process_mode_parent", "pulse_interval", "pulse_f"), &PG_Timers::infinite);

	ClassDB::bind_method(D_METHOD("simple_persistent", "process_mode_parent", "finish_delay", "finish_f"), &PG_Timers::simple_persistent);
	ClassDB::bind_method(D_METHOD("simple_pulse_persistent", "process_mode_parent", "pulse_count", "pulse_f", "finish_delay", "finish_f"), &PG_Timers::simple_pulse_persistent);
	ClassDB::bind_method(D_METHOD("pulse_persistent", "process_mode_parent", "pulse_interval", "pulse_count", "pulse_f", "finish_f"), &PG_Timers::pulse_persistent);
	ClassDB::bind_method(D_METHOD("infinite_persistent", "process_mode_parent", "pulse_interval", "pulse_f"), &PG_Timers::infinite_persistent);

	ClassDB::bind_method(D_METHOD("deferred_one_shot", "process_mode_parent", "f"), &PG_Timers::deferred_one_shot);
#endif
}


Ref<PG_Timers> PG_Timers::mk(PG_SceneTree *stree, PG_Time *time, Ref<PG_Msgr> msgr) {
	return PG_Types::mk_ref<PG_Timers>(stree, time, msgr);
}


PG_Timers::PG_Timers() :
		_stree(nullptr),
		_time(nullptr) {}



PG_Timers::PG_Timers(PG_SceneTree *stree, PG_Time *time, Ref<PG_Msgr> msgr) {
	// DOC: Inserts the first two indices in vector '_timers';
	// Add more if we need a more granular order of execution.
	_timers.append(Vector<Ref<PG_Timer>>());
	_timers.append(Vector<Ref<PG_Timer>>());
	_stree = stree;
	_time = time;
	_msgr = msgr;
	time->connect_to_ticker(callable_mp(this, &PG_Timers::process));
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
