#ifndef PG_SCENE_TREE_H
#define PG_SCENE_TREE_H

#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/types/pg_typedefs.h"
#include "scene/main/scene_tree.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


// TODO: Do a pass on all files and check if _st_ and _if_st_ macros are everywhere.
// TODO: Maybe init all StringNames at start bc their creation is costly.
// Maybe put StringNames in dummy macro, and write Python script to parse files and copy them all to header file.
// https://docs.godotengine.org/en/latest/contributing/development/core_and_modules/core_types.html#stringname


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Cmds;
class PG_FS;
class PG_Msgr;
class PG_SceneTree;
class PG_Session;
class PG_SgnsUser;
class PG_Sys;
class PG_Time;
class PG_Timers;

class Camera3D;
class Node;
class Viewport;
class World3D;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_SceneTree : public SceneTree {
	GDCLASS(PG_SceneTree, SceneTree);
	PG_BIND;


//////////////////////////////////////////////////


protected:
	inline static PG_SceneTree *_singleton;


public:
	static PG_SceneTree *get_sng();


//////////////////////////////////////////////////


protected:
	Ref<PG_Sys> _pg_sys;

	Ref<PG_FS> _pg_fs;

	PG_Time *_pg_time;

	Ref<PG_Timers> _pg_timers;

	Ref<PG_Msgr> _pg_msgr;

	Ref<PG_Cmds> _pg_cmds;

	Ref<PG_Session> _pg_session;

	Ref<PG_SgnsUser> _pg_sgns_user;


//////////////////////////////////////////////////


// TODO: Make const? PG_VR/PG_VP macros too, in that case.
public:
	static PG_SceneTree *get_PG_SceneTree();

	Ref<PG_Sys> get_PG_Sys();

	Ref<PG_FS> get_PG_FS();

	PG_Time *get_PG_Time();

	Ref<PG_Timers> get_PG_Timers();

	Ref<PG_Msgr> get_PG_Msgr();

	Ref<PG_Cmds> get_PG_Cmds();

	Ref<PG_SgnsUser> get_PG_SgnsUser();


//////////////////////////////////////////////////


public:
	PG_INLINE Node *pg_get_root();

	PG_INLINE bool pg_is_paused();


//////////////////////////////////////////////////


// NOTE: NOT IMPLEMENTED:
//func get_global_pos(editor_idx: int = 0) -> Vector2:
//	return pg_get_viewport(editor_idx).get_parent().global_position
//
//func get_size(editor_idx: int = 0) -> Vector2:
//	return pg_get_viewport(editor_idx).size


//////////////////////////////////////////////////


public:
	Viewport *pg_get_viewport(int ed_idx = 0);

	Ref<World3D> get_world_3d(int ed_idx = 0);

	Camera3D *get_main_cam(int ed_idx = 0);

	V2 get_mouse_pos(int ed_idx = 0);


//////////////////////////////////////////////////


public:
	PG_SceneTree();
	~PG_SceneTree();
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_SCENE_TREE_H
