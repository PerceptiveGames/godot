#include "core/object/class_db.h"
#include "core/string/string_name.h"
#include "core/templates/vector.h"
#include "core/variant/array.h"
#include "core/variant/typed_array.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/exts/pg_ta.h"
#include "modules/pg_g1/user/pg_input.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


template <typename T>
TypedArray<T> PG_TA::from_vec(Vector<T> v) {
	TypedArray<T> r;
	for (T e : v) {
		r.append(e);
	}
	return r;
}


//////////////////////////////////////////////////


template <typename T, typename... P>
TypedArray<T> PG_TA::args_to_arr(TypedArray<T> &a, const T &v) {
	a.append(v);
}


template <typename T, typename... P>
TypedArray<T> PG_TA::args_to_arr(TypedArray<T> &a, const T &v, P... args) {
	a.append(v);
	args_to_arr(a, args);
}


template <typename T, typename... P>
TypedArray<T> PG_TA::args_to_arr(P... args) {
	TypedArray<T> r;
	args_to_arr(r, args...);
	return r;
}


//////////////////////////////////////////////////



void PG_TA::_bind_methods() {
#ifdef PG_GD_FNS
#endif
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
