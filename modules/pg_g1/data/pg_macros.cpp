#include "core/string/ustring.h"
#include "core/variant/variant.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/data/pg_paths.h"
#include "modules/pg_g1/types/pg_typedefs.h"



//////////////////////////////////////////////////
//////////////////////////////////////////////////


PSA PG_ST::_st;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


PSA PG_ST::get_st() {
	return _st;
}


// TODO: Check if better with a single fixed-size buffer. Maybe one long string with fixed size.
bool PG_ST::push_back(Str file, Str fn, int line) {
	_st.append(vformat("%s:%s:%d", file.replace(PG_Paths::modules_dir_path(), ""), fn, line));
	return true;
}


void PG_ST::pop_back() {
	if (!_st.is_empty()) {
		_st.remove_at(_st.size() - 1);
	}
}


Str PG_ST::join() {
	return "    " + Str("\n    ").join(_st);
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
