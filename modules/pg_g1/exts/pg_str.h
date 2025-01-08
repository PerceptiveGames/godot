#ifndef PG_STR_H
#define PG_STR_H

#include "core/object/object.h"
#include "modules/pg_g1/data/pg_macros.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class Array;
class String;
class Variant;
struct Vector2;
struct Vector3;

template <typename T>
class TypedArray;

template <typename T>
class Vector;

template <typename K, typename V>
class VMap;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Str : public Object {
	GDCLASS(PG_Str, Object);
	PG_BIND;


//////////////////////////////////////////////////


public:
	PG_INLINE static bool is_str(const Variant &v);


//////////////////////////////////////////////////

	
public:
	PG_INLINE static String to_str(const Variant &v);

	static String to_snake_case(String st);


//////////////////////////////////////////////////


public:
	PG_INLINE static String substr_from_to(String st, int from, int to);

	static TypedArray<String> substr_bw_chars(String st, String bgn_c, String end_c);


//////////////////////////////////////////////////


public:
	static String rm_rpt_chars(String st, String c, bool trim);

	PG_INLINE static String rm_bbcode(String st);


//////////////////////////////////////////////////


public:
	PG_INLINE static String join_non_empty(Vector<String> a, String sep);


//////////////////////////////////////////////////


public:
	static VMap<String, String> parse_kv_pairs(String st, String kv_sep = "=", String pair_sep = "|");


//////////////////////////////////////////////////


public:
	PG_INLINE static bool is_arr_of_str(const Variant &v);


//////////////////////////////////////////////////


public:
	PG_INLINE static TypedArray<String> to_arr_of_str(const Array &a);


//////////////////////////////////////////////////


public:
	// NOTE: Too complicated to turn into VarArgs template, because
	// it needs explicit instantations in .cpp, but there are too many
	// (combinations of variable numbers of String and StringName types).
	// Maybe try to make it work? Maybe String args are enough, and conversions
	// from StringNames and 'char const *' are implicit?
	//template <typename... VarArgs>
	//static TypedArray<String> mk_str_ta(VarArgs... args);

	static TypedArray<String> mk_str_ta(String s0);
	static TypedArray<String> mk_str_ta(String s0, String s1);
	static TypedArray<String> mk_str_ta(String s0, String s1, String s2);
	static TypedArray<String> mk_str_ta(String s0, String s1, String s2, String s3);

};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_STR_H
