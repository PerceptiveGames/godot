#include "core/string/ustring.h"
#include "core/templates/vector.h"
#include "core/variant/variant.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/data/pg_paths.h"



//////////////////////////////////////////////////
//////////////////////////////////////////////////


Vector<String> PG_ST::_st;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


Vector<String> PG_ST::get_st() {
	return _st;
}


// TODO: Check if better with a single fixed-size buffer. Maybe one long string with fixed size.
bool PG_ST::push_back(String file, String fn, int line) {
	_st.append(vformat("%s:%s:%d", file.replace(PG_Paths::modules_dir_path(), ""), fn, line));
	return true;
}


void PG_ST::pop_back() {
	if (!_st.is_empty()) {
		_st.remove_at(_st.size() - 1);
	}
}


String PG_ST::join() {
	return "    " + String("\n    ").join(_st);
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
