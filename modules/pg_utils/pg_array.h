#ifndef PG_ARRAY_H
#define PG_ARRAY_H

#include "core/object/ref_counted.h"
#include "core/string/ustring.h"
#include "core/typedefs.h"


class PGArray : public RefCounted {
	GDCLASS(PGArray, RefCounted);

public:

	//typedef Ref<PGArray> (*CreateFunc)();


private:
	//static CreateFunc create_func[ACCESS_MAX]; ///< set this to instance a filesystem object


protected:
	static void _bind_methods();


public:
	//static Error make_dir_absolute(const String &p_dir);
	int free_nodes_by_predicate(Array *p_array, const Callable &p_callable) const;


	PGArray() {}
	~PGArray() {}
};

#endif // PG_ARRAY_H
