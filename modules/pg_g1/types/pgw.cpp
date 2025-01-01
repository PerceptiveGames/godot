#include "core/object/class_db.h"
#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "core/string/ustring.h"
#include "core/variant/array.h"
#include "core/variant/dictionary.h"
#include "core/variant/typed_array.h"
#include "core/variant/variant.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/types/pgw.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


template <class T>
PG_INLINE bool PGW<T>::ok() {
	return _ok;
}


template <class T>
PG_INLINE bool PGW<T>::nok() {
	return !_ok;
}


template <class T>
T PGW<T>::r() {
	return _r;
}


//////////////////////////////////////////////////


template <class T>
Ref<PGW<T>> PGW<T>::mk_ok() {
	Ref<PGW<T>> inst;
	inst.instantiate();
	inst->_ok = true;
	return inst;
}


template <class T>
Ref<PGW<T>> PGW<T>::mk_nok() {
	Ref<PGW<T>> inst;
	inst.instantiate();
	inst->_ok = false;
	return inst;
}


template <class T>
Ref<PGW<T>> PGW<T>::mk_r(T r) {
	Ref<PGW<T>> inst;
	inst.instantiate();
	inst->_ok = true;
	inst->_r = r;
	return inst;
}


template <class T>
PGW<T>::PGW() : _r(T()) {}


//////////////////////////////////////////////////


template <class T>
PGW<T>::operator bool() const {
	return _ok;
}


//////////////////////////////////////////////////


template <class T>
void PGW<T>::_bind_methods() {
#ifdef PG_GD_FNS
//#define PG_BIND_TPL(tdef)                                                    \
//	ClassDB::bind_method(D_METHOD("ok"), &##tdef::ok);                       \
//	ClassDB::bind_method(D_METHOD("r"), &##tdef::r);                         \
//                                                                             \
//	ClassDB::bind_static_method(#tdef, D_METHOD("mk_ok"), &##tdef::mk_ok);   \
//	ClassDB::bind_static_method(#tdef, D_METHOD("mk_nok"), &##tdef::mk_nok); \
//	ClassDB::bind_static_method(#tdef, D_METHOD("mk_r", "r"), &##tdef::mk_r);
//
//	//ClassDB::bind_method(D_METHOD("msg"), &##tdef::msg); \
//		// TODO: Check args order
//	//ClassDB::bind_static_method(#tdef, D_METHOD("mk_e", "lvl", "id", "details", "e"), &##tdef::_gd_mk_e, DEFVAL(""), DEFVAL(Error::OK)); //\
////\
////		ClassDB::bind_method(D_METHOD("bcast"), &##tdef::bcast); //\
////\
//		//ClassDB::bind_method(D_METHOD("to_str"), &##tdef::to_str); \
//		//ClassDB::bind_method(D_METHOD("to_dict"), &##tdef::to_dict);
//
//	// TODO: Add macro exec for each template/typedef type.
//	PG_BIND_TPL(PGW_Vrt);
//	PG_BIND_TPL(PGW_Str);
//	PG_BIND_TPL(PGW_Arr);
//	PG_BIND_TPL(PGW_ArrStr);
//	//PG_BIND_TPL(PGW_Void);
//#undef PG_BIND_TPL
#endif
}


//////////////////////////////////////////////////


template class PGW<Variant>;
template class PGW<int>;
template class PGW<String>;
template class PGW<Array>;
template class PGW<TypedArray<String>>;
template class PGW<Dictionary>;


//////////////////////////////////////////////////
//////////////////////////////////////////////////
