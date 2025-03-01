#ifndef PG_UI_H
#define PG_UI_H

#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "modules/pg_g1/data/pg_macros.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_UI : public RefCounted {
	GDCLASS(PG_UI, RefCounted);
	PG_BIND;


//////////////////////////////////////////////////


public:
	PG_UI();
	~PG_UI();
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_UI_H
