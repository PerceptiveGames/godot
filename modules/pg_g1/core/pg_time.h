#ifndef PG_TIME_H
#define PG_TIME_H

#include "core/object/object.h"
#include "core/variant/typed_dictionary.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/types/pg_typedefs.h"
#include "scene/main/node.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_SceneTree;
enum Error : int;


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
	int _prev_usec = 0;
	int _curr_usec = 0;
	int _delta_usec = 0;


public:
	int get_delta_usec() const;


//////////////////////////////////////////////////


public:
	template <typename T>
	Error connect_to_ticker(T *instance, void (T::*method)(int));


	template <typename T>
	Error exec_at_next_frame_start(int grp, T *instance, void (T::*method)());


//////////////////////////////////////////////////


protected:
	TD<Vrt, float> _time_scales;


public:
	float get_time_scale(Vrt id);
	float set_time_scale(Vrt id, float v);


//////////////////////////////////////////////////


protected:
	void emit_signals();


//////////////////////////////////////////////////


protected:
	void _notification(int p_what);


//////////////////////////////////////////////////


public:
	PG_Time *init(PG_SceneTree *stree);

	PG_Time();
	~PG_Time();
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_TIME_H
