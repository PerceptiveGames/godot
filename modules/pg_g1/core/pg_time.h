#ifndef PG_TIME_H
#define PG_TIME_H

#include "core/object/object.h"
#include "core/variant/typed_dictionary.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "scene/main/node.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class Callable;
enum Error : int;
class Variant;

class PG_SceneTree;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


// DOC: This class needs to inherit from Node to get per-frame notifications,
// thanks to 'PROCESS_MODE_ALWAYS'. We can't have the contents of this class
// in PG_SceneTree, because its mode is 'PROCESS_MODE_WHEN_PAUSED',
// which shouldn't be changed because we don't want all SceneTree children nodes
// set to inherited process mode to execute their _process() fn.
class PG_Time : public Node {
	GDCLASS(PG_Time, Node);
	PG_BIND;


//////////////////////////////////////////////////


protected:
	PG_SceneTree *_stree;


protected:
	int _prev_usec = 0;
	int _curr_usec = 0;
	int _delta_usec = 0;


public:
	int get_delta_usec() const;


//////////////////////////////////////////////////


public:
	//template <typename T>
	//Error connect_to_ticker(T *instance, void (T::*method)(int));
	Error connect_to_ticker(const Callable &f);


	//template <typename T>
	//Error exec_at_next_frame_start(int grp, T *instance, void (T::*method)());


//////////////////////////////////////////////////


protected:
	TypedDictionary<Variant, float> _time_scales;


public:
	float get_time_scale(Variant id);
	float set_time_scale(Variant id, float v);


//////////////////////////////////////////////////


protected:
	void emit_signals();


//////////////////////////////////////////////////


protected:
	void _notification(int p_what);


//////////////////////////////////////////////////

protected:
	PG_Time *_init(PG_SceneTree *stree);


public:
	static PG_Time *mk(PG_SceneTree *stree);

	PG_Time();
	~PG_Time();
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_TIME_H
