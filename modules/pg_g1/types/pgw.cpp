#include "core/object/class_db.h"
#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "core/string/ustring.h"
#include "core/templates/vector.h"
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
#define PG_BIND_TPL(cls)                                                    \
	ClassDB::bind_method(D_METHOD("ok"), &##cls::ok);                       \
	ClassDB::bind_method(D_METHOD("nok"), &##cls::nok);                     \
	ClassDB::bind_method(D_METHOD("r"), &##cls::r);                         \
                                                                            \
	ClassDB::bind_static_method(#cls, D_METHOD("mk_ok"), &##cls::mk_ok);    \
	ClassDB::bind_static_method(#cls, D_METHOD("mk_nok"), &##cls::mk_nok);  \
	ClassDB::bind_static_method(#cls, D_METHOD("mk_r", "r"), &##cls::mk_r);

	// TODO: Add macro exec for each template/typedef type.
	PG_BIND_TPL(PGW_Vrt);
	PG_BIND_TPL(PGW_Int);
	PG_BIND_TPL(PGW_Str);
	PG_BIND_TPL(PGW_Arr);
	PG_BIND_TPL(PGW_ArrStr);
	PG_BIND_TPL(PGW_Dict);
	PG_BIND_TPL(PGW_VecStr);
#undef PG_BIND_TPL
#endif
}


//////////////////////////////////////////////////


template class PGW<Variant>;
template class PGW<int>;
template class PGW<String>;
template class PGW<Array>;
template class PGW<TypedArray<String>>;
template class PGW<Dictionary>;
template class PGW<Vector<String>>;


//////////////////////////////////////////////////
//////////////////////////////////////////////////
