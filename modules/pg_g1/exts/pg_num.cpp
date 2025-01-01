#include "core/math/random_number_generator.h"
#include "core/object/class_db.h"
#include "core/object/ref_counted.h"
#include "core/variant/typed_array.h"
#include "core/variant/variant.h"
#include "core/variant/variant_utility.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/exts/pg_arr.h"
#include "modules/pg_g1/exts/pg_num.h"
#include "modules/pg_g1/exts/pg_rgx.h"
#include "modules/pg_g1/types/pg_typedefs.h"
#include "modules/pg_g1/types/pg_types.h"
#include "modules/regex/regex.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


Ref<RandomNumberGenerator> PG_Num::_rng;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


bool PG_Num::is_int(const Vrt &v) {
	return v.get_type() == Vrt::INT;
}


bool PG_Num::is_only_digits(Str st) {
	return PG_Rgx::get("only_digits")->search(st) != nullptr;
}


bool PG_Num::is_int_in_rng(Vrt v, int min_incl, int max_incl) {
	if (!PG_Num::is_int(v)) {
		return false;
	}
	int e = PG_Num::to_int(v);
	return e >= min_incl && e <= max_incl;
}


//////////////////////////////////////////////////


int PG_Num::to_int(const Vrt &v) {
	return VUF::type_convert(v, Vrt::INT);
}


int PG_Num::to_int_if_gte(const Vrt &v, const int i) {
	return is_int(v) && to_int(v) >= i ? to_int(v) : -1;
}


int PG_Num::to_int_if_bw(const Vrt &v, const int min_incl, const int max_incl) {
	return is_int(v) && to_int(v) >= min_incl && to_int(v) <= max_incl ? to_int(v) : -1;
}


//////////////////////////////////////////////////


TA<int> PG_Num::to_arr_of_int(const Arr &a) {
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


#ifdef PG_GD_FNS
void PG_Num::_bind_methods() {
	ClassDB::bind_static_method("PG_Num", D_METHOD("is_int", "v"), &PG_Num::is_int);
	ClassDB::bind_static_method("PG_Num", D_METHOD("is_only_digits", "st"), &PG_Num::is_only_digits);
	ClassDB::bind_static_method("PG_Num", D_METHOD("is_int_in_rng", "v", "min_incl", "max_incl"), &PG_Num::is_int_in_rng);

	ClassDB::bind_static_method("PG_Num", D_METHOD("to_int", "v"), &PG_Num::to_int);
	ClassDB::bind_static_method("PG_Num", D_METHOD("to_int_if_gte", "v", "i"), &PG_Num::to_int_if_gte);
	ClassDB::bind_static_method("PG_Num", D_METHOD("to_int_if_bw", "v", "min_incl", "max_incl"), &PG_Num::to_int_if_bw);

	ClassDB::bind_static_method("PG_Num", D_METHOD("get_rnd_int", "min_incl", "max_incl"), &PG_Num::get_rnd_int);
}
#endif


void PG_Num::init() {
	//_rng = memnew(RandomNumberGenerator);
	_rng = PG_Types::mk_ref<RandomNumberGenerator>();
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
