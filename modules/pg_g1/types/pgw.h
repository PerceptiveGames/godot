#ifndef PGW_H
#define PGW_H

#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "modules/pg_g1/data/pg_macros.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


// DOC: This system should maybe not be used with Ref<> types;
// returning nullptr in those cases should be enough.
// TODO: Maybe add a "processed" bool variable if the error has already been processed.
// It could be useful when returning from multiple nested PGWs.
// TODO: Find a way to return r() already cast (int, stringname, obj, node, etc.).
// This will increase dependencies so maybe not.


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class Array;
class ConfigFile;
class Dictionary;
class String;
class Variant;

template <typename T>
class TypedArray;

template <typename T>
class Vector;

template <typename T>
class PGW;


typedef PGW<Variant> PGW_Vrt;
typedef PGW<int> PGW_Int;
typedef PGW<String> PGW_Str;
typedef PGW<Array> PGW_Arr;
typedef PGW<TypedArray<String>> PGW_ArrStr;
typedef PGW<Dictionary> PGW_Dict;
typedef PGW<Vector<String>> PGW_VecStr;

//typedef PGW<Ref<ConfigFile>> PGW_Cfg2;
//typedef PGW<ConfigFile> PGW_Cfg;


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

	static Ref<PGW<T>> mk_r(T r);

	//static Ref<PGW<T>> mk_r_ref(T r);


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
