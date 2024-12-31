#ifndef PG_CHEATS_H
#define PG_CHEATS_H

#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/types/pg_typedefs.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Cheats;
class PG_Cmds;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Cheats : public RefCounted {
	GDCLASS(PG_Cheats, RefCounted);
	PG_BIND;


//////////////////////////////////////////////////


protected:
	Ref<PG_Cmds> _cmds;


//////////////////////////////////////////////////


protected:
	bool _god;

	//void _god_send(PSA args, VMap<SN, Ref<PG_Cmd>> deps);
	void _god_send(PSA args);

	Vrt _god_get() const;


//////////////////////////////////////////////////


public:
	//void _god_send(PSA args, PG_TDDeps deps);

	static Ref<PG_Cheats> mk(Ref<PG_Cmds> cmds);


	PG_Cheats() : _god(false) {}

	PG_Cheats(Ref<PG_Cmds> cmds);
	~PG_Cheats();
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_CHEATS_H
