#include "core/object/class_db.h"
#include "core/templates/vmap.h"
#include "core/variant/typed_array.h"
#include "core/variant/variant.h"
#include "core/variant/variant_utility.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "modules/pg_g1/exts/pg_rgx.h"
#include "modules/pg_g1/exts/pg_str.h"
#include "modules/pg_g1/types/pg_typedefs.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


bool PG_Str::is_str(const Vrt &v) {
	return v.get_type() == Vrt::STRING;
}


//////////////////////////////////////////////////


Str PG_Str::to_str(const Vrt &v) {
	return VUF::type_convert(v, Vrt::STRING);
}


Str PG_Str::to_snake_case(Str st) {
	Str r = st;
	Str cs = ".,!?()[]%&/*-+\"'";
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


Str PG_Str::substr_from_to(Str st, int from, int to) {
	return st.substr(from, to - from);
}


TA<Str> PG_Str::substr_bw_chars(Str st, Str bgn_c, Str end_c) {
	TA<Str> r;
	int srch_bgn = 0;
	while (1) {
		int substr_bgn = st.find(bgn_c, srch_bgn);
		if (substr_bgn < 0) {
			break;
		}
		int substr_end = st.find(end_c, substr_bgn + 1);
		Str t = substr_from_to(st, substr_bgn + 1, substr_end);
		r.append(t);
		srch_bgn = substr_end + 1;
	}
	return r;
}


//////////////////////////////////////////////////


Str PG_Str::rm_rpt_chars(Str st, Str c, bool trim) {
	Str r = PG_Rgx::sub("dbl_spaces", st, c);
	if (trim) {
		r = r.trim_prefix(c).trim_suffix(c);
	}
	return r;
}


Str PG_Str::rm_bbcode(Str st) {
	return PG_Rgx::sub("bbcode_tags", st, "");
}


//////////////////////////////////////////////////


Str PG_Str::join_non_empty(PSA a, Str sep) {
	return sep.join(a).lstrip(sep).rstrip(sep).replace(sep + sep, sep);
}


//////////////////////////////////////////////////


VMap<Str, Str> PG_Str::parse_kv_pairs(Str st, Str kv_sep, Str pair_sep) {
	VMap<Str, Str> r;
	for (Str arg : st.split(pair_sep, false)) {
		PSA p = arg.split(kv_sep, false);
		r[p[0]] = p[1];
	}
	return r;
}


//////////////////////////////////////////////////


#ifdef PG_GD_FNS
void PG_Str::_bind_methods() {
	ClassDB::bind_static_method("PG_Str", D_METHOD("is_str", "v"), &PG_Str::is_str);

	ClassDB::bind_static_method("PG_Str", D_METHOD("to_str", "v"), &PG_Str::to_str);
	ClassDB::bind_static_method("PG_Str", D_METHOD("to_snake_case", "st"), &PG_Str::to_snake_case);

	ClassDB::bind_static_method("PG_Str", D_METHOD("substr_from_to", "st", "from", "to"), &PG_Str::substr_from_to);
	ClassDB::bind_static_method("PG_Str", D_METHOD("substr_bw_chars", "st", "bgn_c", "end_c"), &PG_Str::substr_bw_chars);

	ClassDB::bind_static_method("PG_Str", D_METHOD("rm_rpt_chars", "st", "c", "trim"), &PG_Str::rm_rpt_chars);
	ClassDB::bind_static_method("PG_Str", D_METHOD("rm_bbcode", "st"), &PG_Str::rm_bbcode);

	ClassDB::bind_static_method("PG_Str", D_METHOD("join_non_empty", "a", "sep"), &PG_Str::join_non_empty);
}
#endif


//////////////////////////////////////////////////
//////////////////////////////////////////////////
