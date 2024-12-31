#ifndef PG_TYPES_H
#define PG_TYPES_H

#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/types/pg_typedefs.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Types : public Object {
	GDCLASS(PG_Types, Object);
	PG_BIND;


//////////////////////////////////////////////////


public:
	PG_INLINE static bool to_bool(const Vrt &v);


//////////////////////////////////////////////////


public:
	template <typename T>
	PG_INLINE static Ref<T> *cast_ref(Ref<RefCounted> *o);


//////////////////////////////////////////////////


public:
	template <typename T, typename TR>
	PG_INLINE static TR trn_eq(T lhs, T v0, TR r0, T v1, TR r1, T v2, TR r2, TR df);


	template <typename T, typename TR>
	PG_INLINE static TR trn_eq(T lhs, T v0, TR r0, T v1, TR r1, T v2, TR r2, T v3, TR r3, TR df);


//////////////////////////////////////////////////


public:
	template <typename T, typename... VarArgs>
	PG_INLINE static Ref<T> mk_ref(VarArgs... args) {
		Ref<T> r;
		r.instantiate(args...);
		return r;
	}

	template <typename T>
	PG_INLINE static Ref<T> mk_ref_from_ptr(T *o) {
		Ref<T> r;
		r.reference_ptr(o);
		return r;
	}

	template <typename T>
	PG_INLINE static T unref(T o) {
		o.unref();
		return o;
	}
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_TYPES_H
