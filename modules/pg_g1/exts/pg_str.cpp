#include "core/object/class_db.h"
#include "core/string/ustring.h"
#include "core/templates/vector.h"
#include "core/templates/vmap.h"
#include "core/variant/array.h"
#include "core/variant/typed_array.h"
#include "core/variant/variant.h"
#include "core/variant/variant_utility.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/exts/pg_arr.h"
#include "modules/pg_g1/exts/pg_rgx.h"
#include "modules/pg_g1/exts/pg_str.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


bool PG_Str::is_str(const Variant &v) {
	return v.get_type() == Variant::STRING;
}


//////////////////////////////////////////////////


String PG_Str::to_str(const Variant &v) {
	return VariantUtilityFunctions::type_convert(v, Variant::STRING);
}


String PG_Str::to_snake_case(String st) {
	String r = st;
	String cs = ".,!?()[]%&/*-+\"'";
	for (int i = 0; i < r.length(); i++) {
		for (int j = 0; j < cs.length(); j++) {
			if (r[i] == cs[j]) {
				r.set(i, char32_t('\u0020')); // DOC: Space char
				continue;
			}
		}
	}
	return r.to_snake_case();
}


//////////////////////////////////////////////////


String PG_Str::substr_from_to(String st, int from, int to) {
	return st.substr(from, to - from);
}


TypedArray<String> PG_Str::substr_bw_chars(String st, String bgn_c, String end_c) {
	TypedArray<String> r;
	int srch_bgn = 0;
	while (1) {
		int substr_bgn = st.find(bgn_c, srch_bgn);
		if (substr_bgn < 0) {
			break;
		}
		int substr_end = st.find(end_c, substr_bgn + 1);
		String t = substr_from_to(st, substr_bgn + 1, substr_end);
		r.append(t);
		srch_bgn = substr_end + 1;
	}
	return r;
}


//////////////////////////////////////////////////


String PG_Str::rm_rpt_chars(String st, String c, bool trim) {
	String r = PG_Rgx::sub("dbl_spaces", st, c);
	if (trim) {
		r = r.trim_prefix(c).trim_suffix(c);
	}
	return r;
}


String PG_Str::rm_bbcode(String st) {
	return PG_Rgx::sub("bbcode_tags", st, "");
}


//////////////////////////////////////////////////


String PG_Str::join_non_empty(Vector<String> a, String sep) {
	return sep.join(a).lstrip(sep).rstrip(sep).replace(sep + sep, sep);
}


//////////////////////////////////////////////////


VMap<String, String> PG_Str::parse_kv_pairs(String st, String kv_sep, String pair_sep) {
	VMap<String, String> r;
	for (String arg : st.split(pair_sep, false)) {
		Vector<String> p = arg.split(kv_sep, false);
		r[p[0]] = p[1];
	}
	return r;
}


//////////////////////////////////////////////////


bool PG_Str::is_arr_of_str(const Variant &v) {
	if (!PG_Arr::is_arr(v)) {
		return false;
	}
	for (Variant e : PG_Arr::to_arr(v)) {
		if (!PG_Str::is_str(e)) {
			return false;
		}
	}
	return true;
}


//////////////////////////////////////////////////


TypedArray<String> PG_Str::to_arr_of_str(const Array &a) {
	return PG_Arr::assign<String>(a);
}


//////////////////////////////////////////////////


TypedArray<String> PG_Str::mk_ta_str(String s0) {
	TypedArray<String> a;
	a.append(s0);
	return a;
}


TypedArray<String> PG_Str::mk_ta_str(String s0, String s1) {
	TypedArray<String> a;
	a.append(s0);
	a.append(s1);
	return a;
}


TypedArray<String> PG_Str::mk_ta_str(String s0, String s1, String s2) {
	TypedArray<String> a;
	a.append(s0);
	a.append(s1);
	a.append(s2);
	return a;
}


TypedArray<String> PG_Str::mk_ta_str(String s0, String s1, String s2, String s3) {
	TypedArray<String> a;
	a.append(s0);
	a.append(s1);
	a.append(s2);
	a.append(s3);
	return a;
}


//////////////////////////////////////////////////


void PG_Str::_bind_methods() {
#ifdef PG_GD_FNS


	//ClassDB::bind_static_method("PG_Arr", D_METHOD("is_arr_of_str", "v"), &PG_Arr::is_arr_of_str);


	ClassDB::bind_static_method("PG_Str", D_METHOD("is_str", "v"), &PG_Str::is_str);

	ClassDB::bind_static_method("PG_Str", D_METHOD("to_str", "v"), &PG_Str::to_str);
	ClassDB::bind_static_method("PG_Str", D_METHOD("to_snake_case", "st"), &PG_Str::to_snake_case);

	ClassDB::bind_static_method("PG_Str", D_METHOD("substr_from_to", "st", "from", "to"), &PG_Str::substr_from_to);
	ClassDB::bind_static_method("PG_Str", D_METHOD("substr_bw_chars", "st", "bgn_c", "end_c"), &PG_Str::substr_bw_chars);

	ClassDB::bind_static_method("PG_Str", D_METHOD("rm_rpt_chars", "st", "c", "trim"), &PG_Str::rm_rpt_chars);
	ClassDB::bind_static_method("PG_Str", D_METHOD("rm_bbcode", "st"), &PG_Str::rm_bbcode);

	ClassDB::bind_static_method("PG_Str", D_METHOD("join_non_empty", "a", "sep"), &PG_Str::join_non_empty);
#endif
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
