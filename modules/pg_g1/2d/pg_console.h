#ifndef PG_CONSOLE_H
#define PG_CONSOLE_H

#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "modules/pg_g1/data/pg_macros.h"
#include "scene/gui/panel_container.h"


//////////////////////////////////////////////////
//////////////////////////////////////////////////


// TODO: Add bbcode. Maybe in messages that appear directly over game too.
// https://docs.godotengine.org/en/latest/tutorials/ui/bbcode_in_richtextlabel.html
//String c = trn_eq(msg->lvl, PGE_MsgLevel::WARNING, "yellow", PGE_MsgLevel::ERROR, "red", PGE_MsgLevel::FATAL, "red", "white");
//String s = vformat("[color=aquamarine]%s[/color][color=%s]%s[/color]", pfx, c, msg->txt);


//////////////////////////////////////////////////
//////////////////////////////////////////////////


// TODO: Init as early as possible, just after file logger.
class InputEvent;
class LineEdit;
class RichTextLabel;
class String;

template <typename T>
class Vector;

class PG_Cmds;
class PG_Msgr;
class PG_Timers;


//////////////////////////////////////////////////
//////////////////////////////////////////////////


class PG_Console : public PanelContainer {
	GDCLASS(PG_Console, PanelContainer);
	PG_BIND;


//////////////////////////////////////////////////


protected:
	Ref<PG_Msgr> _msgr;
	Ref<PG_Timers> _timers;
	Ref<PG_Cmds> _cmds;


//////////////////////////////////////////////////


protected:
	RichTextLabel *_output;
	LineEdit *_input;

	Vector<String> _history;
	int _history_idx;


//////////////////////////////////////////////////


public:
	void _show_console();
	void _hide_console();

	void _show_history_prev();
	void _show_history_next();

	void _set_caret_to_end();


//////////////////////////////////////////////////


public:
	virtual void input(const Ref<InputEvent> &e) override;


protected:
	void _text_submitted(String t);


//////////////////////////////////////////////////


public:
	PG_Console();
	PG_Console(Ref<PG_Msgr> msgr, Ref<PG_Timers> timers, Ref<PG_Cmds> cmds);
	~PG_Console();
};


//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif // PG_CONSOLE_H
