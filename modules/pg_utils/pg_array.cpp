#include "pg_array.h"

//#include "core/config/project_settings.h"
//#include "core/io/file_access.h"
//#include "core/os/memory.h"
//#include "core/os/os.h"
//#include "core/templates/local_vector.h"

#include "core/variant/array.h"
#include "scene/main/node.h"


//Error DirAccess::make_dir_absolute(const String &p_dir) {
//	Ref<DirAccess> d = DirAccess::create_for_path(p_dir);
//	return d->make_dir(p_dir);
//}


//Array PGArray::filter(const Callable &p_callable) const {
int PGArray::free_nodes_by_predicate(Array* p_array, const Callable &p_callable) const {
	Array new_arr = p_array->filter(p_callable);

	for (Variant node : new_arr) {
	}

	return 0;
}


void PGArray::_bind_methods() {

	//ClassDB::bind_static_method("DirAccess", D_METHOD("open", "path"), &DirAccess::_open);
	//ClassDB::bind_method(D_METHOD("is_case_sensitive", "path"), &DirAccess::is_case_sensitive);
	//ADD_PROPERTY(PropertyInfo(Variant::BOOL, "include_hidden"), "set_include_hidden", "get_include_hidden");
}
