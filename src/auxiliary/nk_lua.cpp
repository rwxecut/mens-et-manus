#include "auxiliary/nk_lua.h"

#define GUI_ADD_FIELD(field) {gui[#field] = field;}
typedef std::vector<std::string> vector_str;

namespace lua::nk {

	nk_context *ctx;


	void run (LuaFile *LF, nk_context *nkContext) {
		ctx = nkContext;
		LF->call ("render");
	}

	// Binded functions

	bool begin (const char *title, float x, float y, float w, float h, int flags) {
		return (bool) nk_begin (ctx, title, nk_rect (x, y, w, h), (nk_flags) flags);
	}


	void layout_row_dynamic (float height, int cols) {
		nk_layout_row_dynamic (ctx, height, cols);
	}


	void layout_row_static (float height, int item_width, int cols) {
		nk_layout_row_static (ctx, height, item_width, cols);
	}


	void label (const char *str, int flags) {
		nk_label (ctx, str, (nk_flags) flags);
	}


	bool button_label (const char *str) {
		return (bool) nk_button_label (ctx, str);
	}


	bool check_label (const char *str, bool active) {
		return (bool) nk_check_label (ctx, str, active);
	}


	int combo (sol::as_table_t<vector_str> items, int selected, int item_height, float width, float height) {
		const vector_str& strings = items.source;
		std::vector<const char *> cstrings;
		for (auto &str : strings) cstrings.push_back (str.c_str ());
		return nk_combo (ctx, &cstrings[0], cstrings.size (), selected, item_height, nk_vec2 (width, height));
	}


	int combo_separator (const char *items, const char* separator, int selected, int count, int item_height,
	                     float width, float height) {
		return nk_combo_separator (ctx, items, separator[0], selected, count, item_height, nk_vec2 (width, height));
	}


	void finish () {
		nk_end (ctx);
	}


	// Bind functions
	void init (LuaFile *LF) {
		sol::table gui = LF->state.create_named_table ("gui");
		// Bind functions
		GUI_ADD_FIELD (begin);
		GUI_ADD_FIELD (layout_row_dynamic);
		GUI_ADD_FIELD (layout_row_static)
		GUI_ADD_FIELD (label);
		GUI_ADD_FIELD (button_label);
		GUI_ADD_FIELD (check_label);
		GUI_ADD_FIELD (combo);
		GUI_ADD_FIELD (combo_separator);
		GUI_ADD_FIELD (finish);

		/*---------- Export constants ----------*/
		/*----- Window -----*/
		GUI_ADD_FIELD (NK_WINDOW_BORDER);
		GUI_ADD_FIELD (NK_WINDOW_MOVABLE);
		GUI_ADD_FIELD (NK_WINDOW_SCALABLE);
		GUI_ADD_FIELD (NK_WINDOW_CLOSABLE);
		GUI_ADD_FIELD (NK_WINDOW_MINIMIZABLE);
		GUI_ADD_FIELD (NK_WINDOW_NO_SCROLLBAR);
		GUI_ADD_FIELD (NK_WINDOW_TITLE);
		GUI_ADD_FIELD (NK_WINDOW_SCROLL_AUTO_HIDE);
		GUI_ADD_FIELD (NK_WINDOW_BACKGROUND);
		GUI_ADD_FIELD (NK_WINDOW_SCALE_LEFT);
		GUI_ADD_FIELD (NK_WINDOW_NO_INPUT);
		/*----- Text ----- */
		GUI_ADD_FIELD (NK_TEXT_LEFT);
		GUI_ADD_FIELD (NK_TEXT_CENTERED);
		GUI_ADD_FIELD (NK_TEXT_RIGHT);
	}
}
