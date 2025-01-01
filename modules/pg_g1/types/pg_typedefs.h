#ifndef PG_TYPEDEFS_H
#define PG_TYPEDEFS_H


//////////////////////////////////////////////////
//////////////////////////////////////////////////


// TODO: Maybe add PGE_Msg enum and other enums.
// TODO: VMap (not declared here btw) requires including
// its header when declaring a variable of its type.
// A forward declaration is not enough.
// On the other hand, a fwd decl is enough for HashMap.
// What's the difference between the two classes?


//////////////////////////////////////////////////
//////////////////////////////////////////////////


//enum Error; // re-add


//////////////////////////////////////////////////
//////////////////////////////////////////////////

/*
class Array;

using Arr = Array;


//////////////////////////////////////////////////


template<typename T>
class TypedArray;

template <typename T>
using TA = TypedArray<T>;


//////////////////////////////////////////////////


class Dictionary;

using Dict = Dictionary;


//////////////////////////////////////////////////


template <typename K, typename V>
class TypedDictionary;

template <typename K, typename V>
using TD = TypedDictionary<K, V>;


//////////////////////////////////////////////////


template <typename K, typename V>
struct KeyValue;

template <typename K, typename V>
using KV = KeyValue<K, V>;


//////////////////////////////////////////////////


class String;

typedef String Str;


//////////////////////////////////////////////////


class StringName;

typedef StringName SN;


//////////////////////////////////////////////////


class Variant;

typedef Variant Vrt;


//////////////////////////////////////////////////


struct VariantUtilityFunctions;

typedef VariantUtilityFunctions VUF;


//////////////////////////////////////////////////


struct Vector2;

typedef Vector2 V2;


//////////////////////////////////////////////////


struct Vector3;

typedef Vector3 V3;


//////////////////////////////////////////////////


template <typename K>
class Vector;

typedef Vector<String> PSA;
typedef Vector<StringName> SNV;

template <typename T>
using Vec = Vector<T>;
*/

//////////////////////////////////////////////////
//////////////////////////////////////////////////


class Variant;
class String;
class Array;
class Dictionary;

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


#endif // PG_TYPEDEFS_H
