#include "core/object/class_db.h"
#include "core/string/string_name.h"
#include "core/templates/vector.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/exts/pg_sn.h"
#include "pg_vec.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


Vector<StringName> PG_SN::mk_vec_sn(StringName sn0) {
	Vector<StringName> v;
	v.append(sn0);
	return v;
}


Vector<StringName> PG_SN::mk_vec_sn(StringName sn0, StringName sn1) {
	Vector<StringName> v;
	v.append(sn0);
	v.append(sn1);
	return v;
}


Vector<StringName> PG_SN::mk_vec_sn(StringName sn0, StringName sn1, StringName sn2) {
	Vector<StringName> v;
	v.append(sn0);
	v.append(sn1);
	v.append(sn2);
	return v;
}


Vector<StringName> PG_SN::mk_vec_sn(StringName sn0, StringName sn1, StringName sn2, StringName sn3) {
	Vector<StringName> v;
	v.append(sn0);
	v.append(sn1);
	v.append(sn2);
	v.append(sn3);
	return v;
}


//////////////////////////////////////////////////


void PG_SN::_bind_methods() {
#ifdef PG_GD_FNS
#endif
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
