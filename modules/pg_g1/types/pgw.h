#ifndef PGW_H
#define PGW_H

#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "modules/pg_g1/data/pg_macros.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


// TODO: Maybe add a "processed" bool variable if the error has already been processed.
// It could be useful when returning from multiple nested PGWs.
// TODO: Find a way to return r() already cast (int, stringname, obj, node, etc.).
// This will increase dependencies so maybe not.


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class Array;
class Dictionary;
class String;
class Variant;

template <typename T>
class TypedArray;

template <typename T>
class PGW;

// DOC: For each specialization, add call to set_msgr() in PG_SceneTree.
typedef PGW<Variant> PGW_Vrt;
typedef PGW<int> PGW_Int;
typedef PGW<String> PGW_Str;
typedef PGW<Array> PGW_Arr;
typedef PGW<TypedArray<String>> PGW_ArrStr;
typedef PGW<Dictionary> PGW_Dict;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


// DOC: 'W' stands for Wrapper.
template <class T>
class PGW : public RefCounted {
	GDCLASS(PGW, RefCounted);
	PG_BIND;


//////////////////////////////////////////////////


protected:
	bool _ok = false;

	T _r;


//////////////////////////////////////////////////


public:
	bool ok();

	bool nok();

	// DOC: r() can possibly have a valid value even if result is nok().
	// Example: mk_dir() can fail to make a dir, but still return the original path.
	T r();


//////////////////////////////////////////////////


public:
	static Ref<PGW<T>> mk_ok();

	static Ref<PGW<T>> mk_nok();

	// DOC: Keep arg to remove item from array. It helps keep everything on one line.
	static Ref<PGW<T>> mk_r(T r);


//////////////////////////////////////////////////


public:
	PGW();

//////////////////////////////////////////////////


public:
	operator bool() const;
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PGW_H
