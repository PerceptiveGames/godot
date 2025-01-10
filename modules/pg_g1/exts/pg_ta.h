#ifndef PG_TA_H
#define PG_TA_H

#include "core/object/object.h"
#include "modules/pg_g1/data/pg_macros.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


template <typename T>
class TypedArray;

template <typename T>
class Vector;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_TA : public Object {
	GDCLASS(PG_TA, Object);
	PG_BIND;


//////////////////////////////////////////////////


public:
	template <typename T>
	static TypedArray<T> from_vec(Vector<T> v);


//////////////////////////////////////////////////


public:
	template <typename T, typename... P>
	static TypedArray<T> args_to_arr(TypedArray<T> &a, const T &v); 

	template <typename T, typename... P>
	static TypedArray<T> args_to_arr(TypedArray<T> &a, const T &v, P... args); 

	template <typename T, typename... P>
	static TypedArray<T> args_to_arr(P... args);
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_TA_H
