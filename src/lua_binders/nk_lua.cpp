#include "lua_binders/nk_lua.h"
#include <string>
#include <vector>
#include <map>

#define GUI_ADD_FIELD(field) {gui[#field] = field;}
typedef std::vector<std::string> vector_str;
typedef std::map<std::string, float> float_map;
typedef sol::as_table_t<float_map> lua_float_map;

namespace lua::nk {

	nk_context *ctx;


	void init (nk_context *nkContext) {
		ctx = nkContext;
	}


	void run (LuaFile *LF) {
		LF->call ("render");
	}

	// Auxiliary functions

	inline struct nk_rect map2rect (float_map const &map) {
		return nk_rect (map.at ("x"), map.at ("y"), map.at ("w"), map.at ("h"));
	}


	inline float_map rect2map (struct nk_rect const &rect) {
		return {{"x", rect.x},
		        {"y", rect.y},
		        {"w", rect.w},
		        {"h", rect.h}};
	}

	// Binded functions

	bool begin (const char *title, lua_float_map bounds, int flags) {
		return (bool) nk_begin (ctx, title, map2rect (bounds), (nk_flags) flags);
	}


	lua_float_map window_get_bounds () {
		struct nk_rect nk_bounds = nk_window_get_bounds (ctx);
		return lua_float_map (rect2map (nk_bounds));
	}


	bool group_begin (const char *title, int flags) {
		return (bool) nk_group_begin (ctx, title, (nk_flags) flags);
	}


	void group_end () {
		nk_group_end (ctx);
	}


	void layout_row_dynamic (float height, int cols) {
		nk_layout_row_dynamic (ctx, height, cols);
	}


	void layout_row_static (float height, int item_width, int cols) {
		nk_layout_row_static (ctx, height, item_width, cols);
	}


	lua_float_map layout_space_bounds () {
		struct nk_rect nk_bounds = nk_layout_space_bounds (ctx);
		return lua_float_map (rect2map (nk_bounds));
	}


	lua_float_map widget_bounds () {
		struct nk_rect nk_bounds = nk_widget_bounds (ctx);
		return lua_float_map (rect2map (nk_bounds));
	}


	void label (const char *str, int flags) {
		nk_label (ctx, str, (nk_flags) flags);
	}


	void label_wrap (const char *str) {
		nk_label_wrap (ctx, str);
	}


	bool selectable_label (const char *str, int flags, bool selected) {
		int sel = (int) selected;
		nk_selectable_label (ctx, str, (nk_flags) flags, &sel);
		return (bool) sel;
	}


	bool button_label (const char *str) {
		return (bool) nk_button_label (ctx, str);
	}


	bool check_label (const char *str, bool active) {
		return (bool) nk_check_label (ctx, str, active);
	}


	int edit_string (int flags, char* str, int max) {
		//return nk_edit_string_zero_terminated(ctx, flags, str, max, nk_filter_default);
		return 0;
	}


	bool popup_begin (int type, const char *title, int flags, lua_float_map bounds) {
		return (bool) nk_popup_begin (ctx, (nk_popup_type) type, title, (nk_flags) flags, map2rect (bounds));
	}


	void popup_close () {
		nk_popup_close (ctx);
	}


	void popup_end () {
		nk_popup_end (ctx);
	}


	int combo (sol::as_table_t<vector_str> items, int selected, int item_height, float width, float height) {
		const vector_str &strings = items;
		std::vector<const char *> cstrings;
		for (auto &str : strings) cstrings.push_back (str.c_str ());
		return nk_combo (ctx, &cstrings[0], (int) cstrings.size (), selected, item_height, nk_vec2 (width, height));
	}


	int combo_separator (const char *items, const char *separator, int selected, int count, int item_height,
	                     float width, float height) {
		return nk_combo_separator (ctx, items, separator[0], selected, count, item_height, nk_vec2 (width, height));
	}


	void tooltip (const char *str) {
		nk_tooltip (ctx, str);
	}


	bool input_is_mouse_hovering_rect (lua_float_map bounds) {
		struct nk_rect nk_bounds = map2rect (bounds);
		return (bool) nk_input_is_mouse_hovering_rect (&ctx->input, nk_bounds);
	}


	void finish () {
		nk_end (ctx);
	}


	// Bind
	void bind (LuaFile *LF) {
		sol::table gui = LF->state.create_named_table ("gui");
		/*---------- Export functions ----------*/
		GUI_ADD_FIELD (begin);
		GUI_ADD_FIELD (window_get_bounds)
		GUI_ADD_FIELD (group_begin);
		GUI_ADD_FIELD (group_end);
		GUI_ADD_FIELD (layout_row_dynamic);
		GUI_ADD_FIELD (layout_row_static);
		GUI_ADD_FIELD (layout_space_bounds);
		GUI_ADD_FIELD (widget_bounds);
		GUI_ADD_FIELD (label);
		GUI_ADD_FIELD (label_wrap);
		GUI_ADD_FIELD (selectable_label);
		GUI_ADD_FIELD (button_label);
		GUI_ADD_FIELD (check_label);
		GUI_ADD_FIELD (edit_string);
		GUI_ADD_FIELD (popup_begin);
		GUI_ADD_FIELD (popup_close);
		GUI_ADD_FIELD (popup_end);
		GUI_ADD_FIELD (combo);
		GUI_ADD_FIELD (combo_separator);
		GUI_ADD_FIELD (tooltip)
		GUI_ADD_FIELD (input_is_mouse_hovering_rect);
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
		/*--- Text edit -- */
		GUI_ADD_FIELD (NK_EDIT_SIMPLE);
		GUI_ADD_FIELD (NK_EDIT_FIELD);
		GUI_ADD_FIELD (NK_EDIT_BOX);
		GUI_ADD_FIELD (NK_EDIT_EDITOR);
		GUI_ADD_FIELD (NK_EDIT_DEFAULT);
		GUI_ADD_FIELD (NK_EDIT_READ_ONLY);
		GUI_ADD_FIELD (NK_EDIT_AUTO_SELECT);
		GUI_ADD_FIELD (NK_EDIT_SIG_ENTER);
		GUI_ADD_FIELD (NK_EDIT_ALLOW_TAB);
		GUI_ADD_FIELD (NK_EDIT_NO_CURSOR);
		GUI_ADD_FIELD (NK_EDIT_SELECTABLE);
		GUI_ADD_FIELD (NK_EDIT_CLIPBOARD);
		GUI_ADD_FIELD (NK_EDIT_CTRL_ENTER_NEWLINE);
		GUI_ADD_FIELD (NK_EDIT_NO_HORIZONTAL_SCROLL);
		GUI_ADD_FIELD (NK_EDIT_ALWAYS_INSERT_MODE);
		GUI_ADD_FIELD (NK_EDIT_MULTILINE);
		GUI_ADD_FIELD (NK_EDIT_GOTO_END_ON_ACTIVATE);
		GUI_ADD_FIELD (NK_EDIT_ACTIVE);
		GUI_ADD_FIELD (NK_EDIT_INACTIVE);
		GUI_ADD_FIELD (NK_EDIT_ACTIVATED);
		GUI_ADD_FIELD (NK_EDIT_DEACTIVATED);
		GUI_ADD_FIELD (NK_EDIT_COMMITED);
		/*----- Popup ---- */
		GUI_ADD_FIELD (NK_POPUP_STATIC);
		GUI_ADD_FIELD (NK_POPUP_DYNAMIC);
	}
}
