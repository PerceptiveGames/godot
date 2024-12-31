#ifndef PG_TIMERS_H
#define PG_TIMERS_H

#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "core/variant/variant.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/types/pg_typedefs.h"
#include "scene/main/node.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


// TODO: Maybe create timer for execution at end of frame or start of next frame.
// Check dupe functionality in PG_Time.


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Msgr;
class PG_SceneTree;
class PG_Time;

class Callable;


//////////////////////////////////////////////////


class PG_TimerUnit : public RefCounted {
	GDCLASS(PG_TimerUnit, RefCounted);

	friend class PG_Timer;


//////////////////////////////////////////////////


protected:
	int _pass_time;
	int _pass_count;
	Callable _pass_f;
	Vrt _time_scale_id;

	int _pass_time_left;
	int _pass_count_left;


//////////////////////////////////////////////////


protected:
	Ref<PG_TimerUnit> _start(int pass_time, int pass_count, const Callable &pass_f, bool call_f_on_start, Vrt time_scale_id = Vrt::NIL);


	bool _update(PG_Time *time, int delta);


//////////////////////////////////////////////////


//protected:
	//	PG_TimerUnit() = default;
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Timer : public RefCounted {
	GDCLASS(PG_Timer, RefCounted);

	friend class PG_Timers;


//////////////////////////////////////////////////


protected:
	Ref<PG_Msgr> _msgr;


//////////////////////////////////////////////////


protected:
	float _initial_delay;
	float _pulse_interval;
	int _pulse_count;
	Callable _pulse_f;

	float _finish_delay;
	Callable _finish_f;

	bool _persistent;
	bool _safeguard;

	Vrt _time_scale_id;

	Node::ProcessMode _process_mode;
	Node *_process_mode_parent;

	Ref<PG_TimerUnit> _handle_delay;
	Ref<PG_TimerUnit> _handle_pulse;
	Ref<PG_TimerUnit> _handle_finish;

	bool _has_started;
	bool _is_running;


//////////////////////////////////////////////////


public:
	Ref<PG_Timer> initial_delay(float initial_delay);

	Ref<PG_Timer> time_scale_id(Vrt time_scale_id);

	Ref<PG_Timer> process_mode(Node::ProcessMode process_mode);

	const bool is_persistent() const;


//////////////////////////////////////////////////


public:
	void start();

	bool pause();

	bool resume();

	bool restart();

	bool cancel();


//////////////////////////////////////////////////


protected:
	bool _update(PG_Time *time, int delta, bool paused);

	Node::ProcessMode _get_inherited_process_mode(const Node *node) const;

	bool _inherits_null_node();

	bool _gatekeep_by_process_mode(bool paused);

	void _setup_process_mode(Node *process_mode_parent);


//////////////////////////////////////////////////


protected:
	PG_Timer();

//protected:
//	PG_Timer() = default;
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_TimerSimple : public PG_Timer {
	GDCLASS(PG_TimerSimple, PG_Timer);

	friend class PG_Timers;


//////////////////////////////////////////////////


protected:
	Ref<PG_TimerSimple> init(Ref<PG_Msgr> msgr, Node *process_mode_parent, float finish_delay, const Callable &finish_f, bool persistent);


//////////////////////////////////////////////////


//protected:
//	PG_TimerSimple() = default;
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_TimerSimplePulse : public PG_Timer {
	GDCLASS(PG_TimerSimplePulse, PG_Timer);

	friend class PG_Timers;


//////////////////////////////////////////////////


protected:
	Ref<PG_TimerSimplePulse> init(Ref<PG_Msgr> msgr, Node *process_mode_parent, int pulse_count, const Callable &pulse_f, float finish_delay, const Callable &finish_f, bool persistent);


//////////////////////////////////////////////////


//protected:
//	PG_TimerSimplePulse() = default;
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_TimerPulse : public PG_Timer {
	GDCLASS(PG_TimerPulse, PG_Timer);

	friend class PG_Timers;


//////////////////////////////////////////////////


protected:
	Ref<PG_TimerPulse> init(Ref<PG_Msgr> msgr, Node *process_mode_parent, float pulse_interval, int pulse_count, const Callable &pulse_f, const Callable &finish_f, bool persistent);


//////////////////////////////////////////////////


//protected:
//	PG_TimerPulse() = default;
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_TimerInfinitePulse : public PG_Timer {
	GDCLASS(PG_TimerInfinitePulse, PG_Timer);

	friend class PG_Timers;


//////////////////////////////////////////////////


protected:
	Ref<PG_TimerInfinitePulse> init(Ref<PG_Msgr> msgr, Node *process_mode_parent, float pulse_interval, const Callable &pulse_f, bool persistent);


//////////////////////////////////////////////////


//protected:
//	PG_TimerInfinitePulse() = default;
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_TimerDeferredOneShot : public PG_Timer {
	GDCLASS(PG_TimerDeferredOneShot, PG_Timer);

	friend class PG_Timers;


//////////////////////////////////////////////////


protected:
	Ref<PG_TimerDeferredOneShot> init(Ref<PG_Msgr> msgr, Node *process_mode_parent, const Callable &f);


//////////////////////////////////////////////////


//protected:
//	PG_TimerInfinitePulse() = default;
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Timers : public RefCounted {
	GDCLASS(PG_Timers, RefCounted);
	PG_BIND;


//////////////////////////////////////////////////


// TODO: Maybe add clean bool to remove from list at the end, if needed. Default : true ?
// DOC:
// PG_TimerPulse : if interval and count->finish possible(finish delay = interval * count)
// PG_TimerInfinitePulse : if interval and NO count->NO finish
// PG_TimerSimplePulse : if NO interval and count->finish mandatory(interval = finish delay div by count)
// PG_TimerSimple : if NO interval and NO count->finish mandatory


//////////////////////////////////////////////////


protected:
	PG_SceneTree *_stree;

	PG_Time *_time;

	Ref<PG_Msgr> _msgr;


//////////////////////////////////////////////////


protected:
	Vec<Vec<Ref<PG_Timer>>> _timers;

	Ref<PG_Timer> _add(int grp, const Ref<PG_Timer> timer);


//////////////////////////////////////////////////


public:
	// DOC: 'process_mode_parent' can be null.
	Ref<PG_TimerSimple> simple(Node *process_mode_parent, float finish_delay, const Callable &finish_f);

	// DOC: 'process_mode_parent' can be null.
	Ref<PG_TimerSimplePulse> simple_pulse(Node *process_mode_parent, int pulse_count, const Callable &pulse_f, float finish_delay, const Callable &finish_f);

	// DOC: 'process_mode_parent' can be null.
	Ref<PG_TimerPulse> pulse(Node *process_mode_parent, float pulse_interval, int pulse_count, const Callable &pulse_f, const Callable &finish_f);

	// DOC: 'process_mode_parent' can be null.
	Ref<PG_TimerInfinitePulse> infinite(Node *process_mode_parent, float pulse_interval, const Callable &pulse_f);


	// DOC: 'process_mode_parent' can be null.
	Ref<PG_TimerSimple> simple_persistent(Node *process_mode_parent, float finish_delay, const Callable &finish_f);

	// DOC: 'process_mode_parent' can be null.
	Ref<PG_TimerSimplePulse> simple_pulse_persistent(Node *process_mode_parent, int pulse_count, const Callable &pulse_f, float finish_delay, const Callable &finish_f);

	// DOC: 'process_mode_parent' can be null.
	Ref<PG_TimerPulse> pulse_persistent(Node *process_mode_parent, float pulse_interval, int pulse_count, const Callable &pulse_f, const Callable &finish_f);

	// DOC: 'process_mode_parent' can be null.
	Ref<PG_TimerInfinitePulse> infinite_persistent(Node *process_mode_parent, float pulse_interval, const Callable &pulse_f);

	// DOC: 'process_mode_parent' can be null.
	// DOC: Whether it's run at the end of frame or start of next frame should be considered irrelevant impl. details.
	// What's important is that it's run before the other custom timers.
	Ref<PG_TimerDeferredOneShot> deferred_one_shot(Node *process_mode_parent, const Callable &f);


	// TODO: Add timers signaling for await


//////////////////////////////////////////////////


public:
	void process(int delta);


//////////////////////////////////////////////////


public:
	static Ref<PG_Timers> mk(PG_SceneTree *stree, PG_Time *time, Ref<PG_Msgr> msgr);


	PG_Timers();


	PG_Timers(PG_SceneTree *stree, PG_Time *time, Ref<PG_Msgr> msgr);
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_TIMERS_H
