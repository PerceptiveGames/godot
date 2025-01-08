#include "core/math/random_number_generator.h"
#include "core/object/class_db.h"
#include "core/object/ref_counted.h"
#include "core/string/ustring.h"
#include "core/variant/array.h"
#include "core/variant/typed_array.h"
#include "core/variant/variant.h"
#include "core/variant/variant_utility.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/exts/pg_arr.h"
#include "modules/pg_g1/exts/pg_num.h"
#include "modules/pg_g1/exts/pg_rgx.h"
#include "modules/pg_g1/types/pg_types.h"
#include "modules/regex/regex.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


Ref<RandomNumberGenerator> PG_Num::_rng;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


bool PG_Num::is_int(const Variant &v) {
	return v.get_type() == Variant::INT;
}


bool PG_Num::is_only_digits(String st) {
	return PG_Rgx::get("only_digits")->search(st) != nullptr;
}


bool PG_Num::is_int_in_rng(Variant v, int min_incl, int max_incl) {
	if (!PG_Num::is_int(v)) {
		return false;
	}
	int e = PG_Num::to_int(v);
	return e >= min_incl && e <= max_incl;
}


//////////////////////////////////////////////////


int PG_Num::to_int(const Variant &v) {
	return VariantUtilityFunctions::type_convert(v, Variant::INT);
}


int PG_Num::to_int_if_gte(const Variant &v, const int i) {
	return is_int(v) && to_int(v) >= i ? to_int(v) : -1;
}


int PG_Num::to_int_if_bw(const Variant &v, const int min_incl, const int max_incl) {
	return is_int(v) && to_int(v) >= min_incl && to_int(v) <= max_incl ? to_int(v) : -1;
}


//////////////////////////////////////////////////


bool PG_Num::is_i32vec(const Variant &v) {
	return v.get_type() == Variant::PACKED_INT32_ARRAY;
}


bool PG_Num::is_i64vec(const Variant &v) {
	return v.get_type() == Variant::PACKED_INT64_ARRAY;
}


//////////////////////////////////////////////////


TypedArray<int> PG_Num::to_arr_of_int(const Array &a) {
	return PG_Arr::assign<int>(a);
}


//////////////////////////////////////////////////


Ref<RandomNumberGenerator> const PG_Num::get_rng() {
	return _rng;
}


int PG_Num::get_rnd_int(int min_incl, int max_incl) {
	return get_rng()->randi_range(min_incl, max_incl);
}


//////////////////////////////////////////////////


void PG_Num::_bind_methods() {
#ifdef PG_GD_FNS
	ClassDB::bind_static_method("PG_Num", D_METHOD("is_int", "v"), &PG_Num::is_int);
	ClassDB::bind_static_method("PG_Num", D_METHOD("is_only_digits", "st"), &PG_Num::is_only_digits);
	ClassDB::bind_static_method("PG_Num", D_METHOD("is_int_in_rng", "v", "min_incl", "max_incl"), &PG_Num::is_int_in_rng);

	ClassDB::bind_static_method("PG_Num", D_METHOD("to_int", "v"), &PG_Num::to_int);
	ClassDB::bind_static_method("PG_Num", D_METHOD("to_int_if_gte", "v", "i"), &PG_Num::to_int_if_gte);
	ClassDB::bind_static_method("PG_Num", D_METHOD("to_int_if_bw", "v", "min_incl", "max_incl"), &PG_Num::to_int_if_bw);

	ClassDB::bind_static_method("PG_Num", D_METHOD("is_i32vec", "v"), &PG_Num::is_i32vec);
	ClassDB::bind_static_method("PG_Num", D_METHOD("is_i64vec", "v"), &PG_Num::is_i64vec);

	ClassDB::bind_static_method("PG_Num", D_METHOD("to_arr_of_int", "a"), &PG_Num::to_arr_of_int);

	ClassDB::bind_static_method("PG_Num", D_METHOD("get_rnd_int", "min_incl", "max_incl"), &PG_Num::get_rnd_int);
#endif
}


void PG_Num::init() {
	//_rng = memnew(RandomNumberGenerator);
	_rng = PG_Types::mk_ref<RandomNumberGenerator>();
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
