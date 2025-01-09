#ifndef PG_SIGNALS_USER_H
#define PG_SIGNALS_USER_H

#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "modules/pg_g1/data/pg_macros.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_SignalsUser : public RefCounted {
	GDCLASS(PG_SignalsUser, RefCounted);
	PG_BIND;


//////////////////////////////////////////////////


public:
	static Ref<PG_SignalsUser> mk();

	PG_SignalsUser();

	~PG_SignalsUser();
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_SIGNALS_USER_H
