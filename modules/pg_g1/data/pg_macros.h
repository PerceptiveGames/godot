#ifndef PG_MACROS_H
#define PG_MACROS_H

#include "core/config/engine.h"
#include "core/object/callable_method_pointer.h"
#include "modules/pg_g1/types/pg_typedefs.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


// TODO: Surround fns with '#ifdef PG_GD_FNS' if they're specialized versions
// only used in '_bind_methods()'.
// TODO:
//BIND_ENUM_CONSTANT(PRIORITY_LOW);
//BIND_ENUM_CONSTANT(PRIORITY_NORMAL);
//BIND_ENUM_CONSTANT(PRIORITY_HIGH);


// FINAL OPTIMIZATIONS (IF NEEDED!):
// - Inherit from TypedArray. Create new fn to replace append().
//   Add multiple slots instead of only doing +1 like append() does.
//   Resize back at the end. Keep internal counter indicating count of actual valid values.
// - Try to avoid reassigning strings to new memory.
// - Check if passing String and Variant types by reference shows perf improvement.
//   In fns where a param passed by value is modified in the fn body, we'll need to make
//   a copy of that param first, within the fn.


//////////////////////////////////////////////////


//template <typename T, typename, typename>
//class HashSet;
//
//struct VariantUtilityFunctions;
//
//template <typename K, typename V>
//class TypedDictionary;
//
//
////////////////////////////////////////////////////
//
//
//typedef Variant Vrt;
//typedef VariantUtilityFunctions VUF;
//typedef String Str;
//typedef StringName SN;
//typedef PackedStringArray PSA;
//typedef Vector<SN> SNV;
//
//template <typename T>
////using Vct = Vector<T>;
//using Vec = Vector<T>;
//
//typedef Array Arr;
//template <typename T>
//using TA = TypedArray<T>;
//
//using Dict = Dictionary;
//template <typename K, typename V>
//using TD = TypedDictionary<K, V>;
//
//template <typename V>
//using HS = HashSet<V>;
//template <typename K, typename V>
//using HM = VMap<K, V>;
//template <typename K, typename V>
//using KV = KeyValue<K, V>;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_SceneTree;
//class PSA;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#define PG_DEBUG_EDITOR 1
#define PG_DEBUG_PRIVATE 2
#define PG_DEBUG_PUBLIC 3
#define PG_RELEASE 4


//////////////////////////////////////////////////


// TODO: Move to another file, so it can stay at the top.
#define PG_BUILD_LEVEL PG_DEBUG_EDITOR
// DOC: Include GDScript versions of functions.
//#define PG_GD_FNS 1

#define ENABLE_INLINE 0


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#if PG_BUILD_LEVEL < PG_RELEASE
	#define PG_STACK_TRACE 1
#endif


//////////////////////////////////////////////////


// TODO: Only add to stack if we're on main thread.
// Alt: create a version that handles multithreading.
#ifdef PG_STACK_TRACE
	#define _pg_push_ PG_ST::push_back(__FILE__, __FUNCTION__, __LINE__)
	#define _pg_pop_ PG_ST::pop_back()

	#define _st_(instr) _pg_push_; instr; _pg_pop_;
	#define _if_st_(cond) _pg_push_; auto _retval_ = cond; _pg_pop_; if(_retval_)
	#define _return_st_(instr) { _pg_push_; auto _retval_ = instr; _pg_pop_; return _retval_; }

	#define _join_st_ PG_ST::join()
	#define _get_st_ PG_ST::get_st()


	//class PG_ST : public RefCounted {
	class PG_ST {
	//GDCLASS(PG_ST, RefCounted);


	protected:
		static PSA _st;


	public:
		static PSA get_st();

		static bool push_back(Str file, Str fn, int line);

		static void pop_back();

		static Str join();
	};


#else
	#define _pg_push_
	#define _pg_pop_

	#define _st_(instr) instr;
	#define _if_st_(cond) if (cond)
	#define _return_st_(instr) return instr;

	#define _join_st_
	#define _get_st_
#endif // PG_STACK_TRACE


//////////////////////////////////////////////////


#if PG_BUILD_LEVEL == PG_DEBUG_EDITOR
	#define PG_IS_EDITOR Engine::get_singleton()->is_editor_hint()
#else
	// Compiler should be able to get rid of the whole condition since it's a constant at 'false'.
	#define PG_IS_EDITOR false
#endif

#if PG_BUILD_LEVEL < PG_RELEASE
	#define PG_NOT_RELEASE true
#else
	// Compiler should be able to get rid of the whole condition since it's a constant at 'false'.
	#define PG_NOT_RELEASE false
#endif


//////////////////////////////////////////////////


// DOC: Used in static function body, when accessing directly.
#define PG_S(cls) cls::get_singleton()

// DOC: Used in static function body, when accessing directly.
#define PG_I(cls) PG_SceneTree::get_sng()->get_##cls()


// DOC: Used in static function body, as the first statement.
#define PG_VR(cls) Ref<##cls> s = PG_I(cls);
#define PG_VP(cls) cls *const s = PG_I(cls);


//////////////////////////////////////////////////


#ifdef PG_GD_FNS
	#define PG_BIND \
		protected: \
		static void _bind_methods();
#else
	#define PG_BIND
#endif


//////////////////////////////////////////////////


#if ENABLE_INLINE == 1
	#define PG_INLINE PG_INLINE
#else
	#define PG_INLINE
#endif



//////////////////////////////////////////////////


#define defer(inst, f) callable_mp(inst, &f).call_deferred();


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_MACROS_H
