#include "auxiliary/nk_lua.h"


namespace lua::nk {

	nk_context *ctx;


	void init (LuaFile *LF) {
		sol::table gui = LF->state.create_named_table ("gui");
		// Bind functions
		gui["begin"] = begin;
		gui["layout_row_dynamic"] = layout_row_dynamic;
		gui["layout_row_static"] = layout_row_static;
		gui["button_label"] = button_label;
		gui["finish"] = finish;

		// Export constants
		gui["NK_WINDOW_BORDER"] = NK_WINDOW_BORDER;
		gui["NK_WINDOW_MOVABLE"] = NK_WINDOW_MOVABLE;
		gui["NK_WINDOW_SCALABLE"] = NK_WINDOW_SCALABLE;
		gui["NK_WINDOW_CLOSABLE"] = NK_WINDOW_CLOSABLE;
		gui["NK_WINDOW_MINIMIZABLE"] = NK_WINDOW_MINIMIZABLE;
		gui["NK_WINDOW_NO_SCROLLBAR"] = NK_WINDOW_NO_SCROLLBAR;
		gui["NK_WINDOW_TITLE"] = NK_WINDOW_TITLE;
		gui["NK_WINDOW_SCROLL_AUTO_HIDE"] = NK_WINDOW_SCROLL_AUTO_HIDE;
		gui["NK_WINDOW_BACKGROUND"] = NK_WINDOW_BACKGROUND;
		gui["NK_WINDOW_SCALE_LEFT"] = NK_WINDOW_SCALE_LEFT;
		gui["NK_WINDOW_NO_INPUT"] = NK_WINDOW_NO_INPUT;
	}


	void run (LuaFile *LF, nk_context *nkContext) {
		lua::nk::ctx = nkContext;
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


	bool button_label (const char *title) {
		return (bool) nk_button_label (ctx, title);
	}


	bool finish () {
		nk_end (ctx);
	}

}
