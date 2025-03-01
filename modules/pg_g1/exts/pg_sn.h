#ifndef PG_SN_H
#define PG_SN_H

#include "core/object/object.h"
#include "modules/pg_g1/data/pg_macros.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class StringName;

template <typename T>
class TypedArray;

template <typename T>
class Vector;

class PG_Vec;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_SN : public Object {
	GDCLASS(PG_SN, Object);
	PG_BIND;


//////////////////////////////////////////////////


//public:
//	TypedArray<StringName> to_sn_arr(const Vector<StringName> &v);


//////////////////////////////////////////////////


public:
	// TODO: Also create mk_arr_sn() if necessary,
	// using PG_Arr::args_to_arr().
	static Vector<StringName> mk_vec_sn(StringName sn0);
	static Vector<StringName> mk_vec_sn(StringName sn0, StringName sn1);
	static Vector<StringName> mk_vec_sn(StringName sn0, StringName sn1, StringName sn2);
	static Vector<StringName> mk_vec_sn(StringName sn0, StringName sn1, StringName sn2, StringName sn3);
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_SN_H
