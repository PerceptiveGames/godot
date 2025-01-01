#include "core/object/class_db.h"
#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "core/variant/variant.h"
#include "core/variant/variant_utility.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/types/pg_types.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


bool PG_Types::to_bool(const Variant &v) {
	return VariantUtilityFunctions::type_convert(v, Variant::BOOL);
}


//////////////////////////////////////////////////


template <typename T>
Ref<T> *PG_Types::cast_ref(Ref<RefCounted> *o) {
	return Object::cast_to<T>(o);
}


//////////////////////////////////////////////////


template <typename T, typename TR>
TR PG_Types::trn_eq(T lhs, T v0, TR r0, T v1, TR r1, T v2, TR r2, TR df) {
	if (lhs == v0) {
		return r0;
	}
	if (lhs == v1) {
		return r1;
	}
	if (lhs == v2) {
		return r2;
	}
	return df;
}


template <typename T, typename TR>
TR PG_Types::trn_eq(T lhs, T v0, TR r0, T v1, TR r1, T v2, TR r2, T v3, TR r3, TR df) {
	if (lhs == v0) {
		return r0;
	}
	if (lhs == v1) {
		return r1;
	}
	if (lhs == v2) {
		return r2;
	}
	if (lhs == v3) {
		return r3;
	}
	return df;
}


//////////////////////////////////////////////////


void PG_Types::_bind_methods() {
#ifdef PG_GD_FNS
	ClassDB::bind_static_method("PG_Types", D_METHOD("to_bool", "v"), &PG_Types::to_bool);
#endif
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
