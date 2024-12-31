#ifndef PG_ARR_H
#define PG_ARR_H

#include "core/object/object.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/types/pg_typedefs.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


// TODO: Add method variants using templates where Vrt is used.
// Do not delete existing Vrt ones.
// Also do that in other classes.


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class Callable;
class Node3D;
enum class Key;
//enum class Key : unsigned int;

//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Arr : public Object {
	GDCLASS(PG_Arr, Object);
	PG_BIND;


//////////////////////////////////////////////////


public:
	PG_INLINE static bool is_arr(const Vrt &v);


	PG_INLINE static bool is_arr_of_str(const Vrt &v);


//////////////////////////////////////////////////


public:
	PG_INLINE static Arr to_arr(const Vrt &v);


	PG_INLINE static TA<int> to_arr_of_int(const Arr &a);


	PG_INLINE static TA<V2> to_arr_of_v2(const Arr &a);


	PG_INLINE static TA<V3> to_arr_of_v3(const Arr &a);


	PG_INLINE static TA<Str> to_arr_of_str(const Arr &a);


	PG_INLINE static TA<Node3D> to_arr_of_node_3d(const Arr &a);


	static Vec<Key> to_arr_of_valid_keycodes(const Vrt &v);


	PG_INLINE static Arr from_pair(const Pair<Vrt, Vrt> &v);


//////////////////////////////////////////////////


public:
	// TODO: Make separate functions with 1, 2, 3, 4 args instead of defaults?
	static TA<Str> mk_ta_str(Str s1 = "", Str s2 = "", Str s3 = "", Str s4 = "");


	static SNV mk_snv(SN s1 = "", SN s2 = "", SN s3 = "", SN s4 = "");


//////////////////////////////////////////////////


public:
	PG_INLINE static bool idx_ok(const Arr &a, int i);

	template <typename T>
	PG_INLINE static bool idx_ok(const Vec<T> &v, int i);


	template <typename T>
	PG_INLINE static T get_by_idx(const Vec<T> &v, int idx, T &def);

#ifdef PG_GD_FNS
	static Vrt _gd_get_by_idx(const Arr &a, int idx, const Vrt &def = Vrt::NIL);
#endif


	template <typename T>
	PG_INLINE static T get_by_idx_wrap(const Vec<T> &v, int idx, T &def);

#ifdef PG_GD_FNS
	static Vrt _gd_get_by_idx_wrap(const Arr &a, int idx, const Vrt &def = Vrt::NIL);
#endif


	// DOC: Same as Array::back() except it doesn't generate an error if array is empty.
	template <class T>
	PG_INLINE static T last(const Vec<T> &v, T &def);

#ifdef PG_GD_FNS
	// DOC: Same as Array::back() except it doesn't generate an error if array is empty.
	static Vrt _gd_last(const Arr &a, const Vrt &def = Vrt::NIL);
#endif


	template <class T>
	PG_INLINE static T penultimate(const Arr &v, T &def);

#ifdef PG_GD_FNS
	static Vrt _gd_penultimate(const Arr &a, const Vrt &def = Vrt::NIL);
#endif


	static TA<int> find_idxs(const Arr &a, const Vrt &v);


	static bool has_any_in_common(const Arr &a1, const Arr &a2);


	// DOC: Returns the index of the first value found in 'a' that is approx equal to 'v', or -1.
	static int get_approx_v_idx(const Arr &a, const Vrt &v);


//////////////////////////////////////////////////


public:
	static bool set_last(Arr &a, const Vrt &v, bool add_if_empty = true);


	static bool append_if_diff_from_last(Arr &a, const Vrt &v);


//////////////////////////////////////////////////


public:
	// DOC: Use T = *P if Arr is made of Objects. Should also be able to use Ref<T>.
	template <typename T>
	static T first_f(const Vec<T> &v, const Callable &f, T &def);

#ifdef PG_GD_FNS
	static Vrt _gd_first_f(const Arr &a, const Callable &f, const Vrt &def = Vrt::NIL);
#endif


//////////////////////////////////////////////////


public:
	static int rm_all_v(Arr &a, const Vrt &v);


	static int rm_adj_dupes(Arr &a);


	// DOC: Returns the number of items removed.
	static int mk_unique(Arr &a);


	template<typename T>
	static int resize_until_item(Vec<T> &v, const T &item, bool pop_found_item);


	// DOC: Has _gd prefix to differentiate from native method and to be able to bind to GD.
	// DOC: It can still be used in C++.
	// NOTE: Was 'pop_back_until_found()'.
	static int _gd_resize_until_item(Arr &a, const Vrt &item, bool pop_found_item);


//////////////////////////////////////////////////


public:
	template <typename T>
	static TA<T> assign(const Arr &a);


	// DOC: Has _gd prefix to differentiate from native method and to be able to bind to GD.
	// DOC: It can still be used in C++.
	static Arr _gd_assign(const Arr &from, Arr &to);


//////////////////////////////////////////////////


public:
	template <typename T>
	static TA<T> get_interleaved(const TA<T> &a, const T &item, bool also_if_empty = false);


//////////////////////////////////////////////////


public:
	template <typename T>
	static TA<T> args_to_arr(const T &arg0, const T &arg1, const T &arg2, const T &arg3, const T &arg4, const T &arg5);

	template <typename T>
	static TA<T> args_to_arr(const T &arg0, const T &arg1, const T &arg2, const T &arg3, const T &arg4);

	template <typename T>
	static TA<T> args_to_arr(const T &arg0, const T &arg1, const T &arg2, const T &arg3);

	template <typename T>
	static TA<T> args_to_arr(const T &arg0, const T &arg1, const T &arg2);

	template <typename T>
	static TA<T> args_to_arr(const T &arg0, const T &arg1);
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_ARR_H
