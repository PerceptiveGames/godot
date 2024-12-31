#include "core/config/engine.h"
#include "core/object/callable_method_pointer.h"
#include "core/object/object.h"
#include "core/os/time.h"
#include "core/string/string_name.h"
#include "core/string/ustring.h"
#include "core/typedefs.h"
#include "modules/pg_g1/core/pg_scene_tree.h"
#include "modules/pg_g1/core/pg_time.h"
#include "modules/pg_g1/core/pg_timers.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/types/pg_typedefs.h"
#include "scene/main/node.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


int PG_Time::get_delta_usec() const {
	return _delta_usec;
}


//////////////////////////////////////////////////


template <typename T>
Error PG_Time::connect_to_ticker(T *instance, void (T::*method)(int)) {
	return connect("process", callable_mp(instance, method));
}
template Error PG_Time::connect_to_ticker<PG_Timers>(PG_Timers *instance, void (PG_Timers::*method)(int));


template <typename T>
Error PG_Time::exec_at_next_frame_start(int grp, T *instance, void (T::*method)()) {
	return connect("frame_started_" + itos(grp), callable_mp(instance, method), CONNECT_ONE_SHOT);
}


//////////////////////////////////////////////////


float PG_Time::get_time_scale(Vrt id) {
	// TODO: Look at 'Engine.time_scale' doc to also update physics timescale when changing 'Engine.time_scale' value.
	// TODO: nullptr check means id can only be pointer type
	return (id != nullptr) ? float(_time_scales[id]) : PG_S(Engine)->get_time_scale();
}


float PG_Time::set_time_scale(Vrt id, float v) {
	float old = _time_scales.has(id) ? float(_time_scales[id]) : -1.0;
	_time_scales[id] = CLAMP(v, 0.0, 1.0);
	return old;
}


//////////////////////////////////////////////////


void PG_Time::emit_signals() {
	emit_signal(SNAME("frame_started_0"));
	emit_signal(SNAME("frame_started_1"));
	emit_signal(SNAME("frame_started_2"));
}


//////////////////////////////////////////////////


// TODO: Make sure this gets executed before other PG NOTIFICATION_PROCESS notis.
// Maybe put exec in PG_Time::emit_signals().
void PG_Time::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_PROCESS: {
			_prev_usec = _curr_usec;
			_curr_usec = PG_S(Time)->get_ticks_usec();
			_delta_usec = _curr_usec - _prev_usec;

			emit_signal(SNAME("process"), _delta_usec);
			// DOC: If emitting order is important, create multiple groups
			// instead by emitting e.g. process_group_0, process_group_1, etc.
			// in order.
		}
	}
}


//////////////////////////////////////////////////


#ifdef PG_GD_FNS
void PG_Time::_bind_methods() {
	ADD_SIGNAL(MethodInfo("process", PropertyInfo(Vrt::INT, "delta")));

	ADD_SIGNAL(MethodInfo("frame_started_0"));
	ADD_SIGNAL(MethodInfo("frame_started_1"));
	ADD_SIGNAL(MethodInfo("frame_started_2"));
}
#endif


PG_Time *PG_Time::init(PG_SceneTree *stree) {
	stree->connect("process_frame", callable_mp(this, &PG_Time::emit_signals));
	return this;
}


PG_Time::PG_Time() {
	set_process_mode(Node::PROCESS_MODE_ALWAYS);
}


PG_Time::~PG_Time() {
	// TODO: Disconnect from ctor signals.
	// TODO: Add log message "Destroying PG_Time singleton. This should only happen when quitting the game."
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
