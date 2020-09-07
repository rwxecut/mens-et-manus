#include "lua_binders/nk_lua.h"
#include "lua_binders/buffer_lua.h"

namespace lua::bind {

	Nuklear::Nuklear (File *LF) : Bind (LF) {
		// Usertype for Nuklear GUI functions bindings should not be directly used in scripts
		auto nk = LF->state.new_usertype<Nuklear> ("__NuklearBindingType");
		/*---------- Export functions ----------*/
		#define NK_EXPORT_METHOD(field) {nk[#field] = &Nuklear::field;}
		NK_EXPORT_METHOD (begin);
		NK_EXPORT_METHOD (window_get_bounds)
		NK_EXPORT_METHOD (group_begin);
		NK_EXPORT_METHOD (group_end);
		NK_EXPORT_METHOD (layout_row_dynamic);
		NK_EXPORT_METHOD (layout_row_static);
		NK_EXPORT_METHOD (layout_space_bounds);
		NK_EXPORT_METHOD (widget_bounds);
		NK_EXPORT_METHOD (label);
		NK_EXPORT_METHOD (label_wrap);
		NK_EXPORT_METHOD (selectable_label);
		NK_EXPORT_METHOD (button_label);
		NK_EXPORT_METHOD (check_label);
		NK_EXPORT_METHOD (edit_string);
		NK_EXPORT_METHOD (popup_begin);
		NK_EXPORT_METHOD (popup_close);
		NK_EXPORT_METHOD (popup_end);
		NK_EXPORT_METHOD (combo);
		NK_EXPORT_METHOD (combo_separator);
		NK_EXPORT_METHOD (tooltip)
		NK_EXPORT_METHOD (input_is_mouse_hovering_rect);
		NK_EXPORT_METHOD (finish);
		#undef NK_EXPORT_METHOD
		/*---------- Export constants ----------*/
		#define NK_EXPORT_CONSTANT(field) {nk[#field] = sol::var(field);}
		/*----- Window -----*/
		NK_EXPORT_CONSTANT (NK_WINDOW_BORDER);
		NK_EXPORT_CONSTANT (NK_WINDOW_MOVABLE);
		NK_EXPORT_CONSTANT (NK_WINDOW_SCALABLE);
		NK_EXPORT_CONSTANT (NK_WINDOW_CLOSABLE);
		NK_EXPORT_CONSTANT (NK_WINDOW_MINIMIZABLE);
		NK_EXPORT_CONSTANT (NK_WINDOW_NO_SCROLLBAR);
		NK_EXPORT_CONSTANT (NK_WINDOW_TITLE);
		NK_EXPORT_CONSTANT (NK_WINDOW_SCROLL_AUTO_HIDE);
		NK_EXPORT_CONSTANT (NK_WINDOW_BACKGROUND);
		NK_EXPORT_CONSTANT (NK_WINDOW_SCALE_LEFT);
		NK_EXPORT_CONSTANT (NK_WINDOW_NO_INPUT);
		/*----- Text ----- */
		NK_EXPORT_CONSTANT (NK_TEXT_LEFT);
		NK_EXPORT_CONSTANT (NK_TEXT_CENTERED);
		NK_EXPORT_CONSTANT (NK_TEXT_RIGHT);
		/*--- Text edit -- */
		NK_EXPORT_CONSTANT (NK_EDIT_SIMPLE);
		NK_EXPORT_CONSTANT (NK_EDIT_FIELD);
		NK_EXPORT_CONSTANT (NK_EDIT_BOX);
		NK_EXPORT_CONSTANT (NK_EDIT_EDITOR);
		NK_EXPORT_CONSTANT (NK_EDIT_DEFAULT);
		NK_EXPORT_CONSTANT (NK_EDIT_READ_ONLY);
		NK_EXPORT_CONSTANT (NK_EDIT_AUTO_SELECT);
		NK_EXPORT_CONSTANT (NK_EDIT_SIG_ENTER);
		NK_EXPORT_CONSTANT (NK_EDIT_ALLOW_TAB);
		NK_EXPORT_CONSTANT (NK_EDIT_NO_CURSOR);
		NK_EXPORT_CONSTANT (NK_EDIT_SELECTABLE);
		NK_EXPORT_CONSTANT (NK_EDIT_CLIPBOARD);
		NK_EXPORT_CONSTANT (NK_EDIT_CTRL_ENTER_NEWLINE);
		NK_EXPORT_CONSTANT (NK_EDIT_NO_HORIZONTAL_SCROLL);
		NK_EXPORT_CONSTANT (NK_EDIT_ALWAYS_INSERT_MODE);
		NK_EXPORT_CONSTANT (NK_EDIT_MULTILINE);
		NK_EXPORT_CONSTANT (NK_EDIT_GOTO_END_ON_ACTIVATE);
		NK_EXPORT_CONSTANT (NK_EDIT_ACTIVE);
		NK_EXPORT_CONSTANT (NK_EDIT_INACTIVE);
		NK_EXPORT_CONSTANT (NK_EDIT_ACTIVATED);
		NK_EXPORT_CONSTANT (NK_EDIT_DEACTIVATED);
		NK_EXPORT_CONSTANT (NK_EDIT_COMMITED);
		/*----- Popup ---- */
		NK_EXPORT_CONSTANT (NK_POPUP_STATIC);
		NK_EXPORT_CONSTANT (NK_POPUP_DYNAMIC);
		#undef NK_EXPORT_CONSTANT
	}


	void Nuklear::init (nk_context *nkContext) {
		ctx = nkContext;
	}


	nk_context *Nuklear::ctx;


	/*---------- Auxiliary functions ----------*/

	inline struct nk_rect Nuklear::map2rect (float_map const &map) {
		return nk_rect (map.at ("x"), map.at ("y"), map.at ("w"), map.at ("h"));
	}


	inline Nuklear::float_map Nuklear::rect2map (struct nk_rect const &rect) {
		return {{"x", rect.x},
		        {"y", rect.y},
		        {"w", rect.w},
		        {"h", rect.h}};
	}


	/*---------- Binded functions ----------*/

	bool Nuklear::begin (const char *title, lua_float_map bounds, int flags) {
		return (bool) nk_begin (ctx, title, map2rect (bounds), (nk_flags) flags);
	}


	Nuklear::lua_float_map Nuklear::window_get_bounds () {
		struct nk_rect nk_bounds = nk_window_get_bounds (ctx);
		return lua_float_map (rect2map (nk_bounds));
	}


	bool Nuklear::group_begin (const char *title, int flags) {
		return (bool) nk_group_begin (ctx, title, (nk_flags) flags);
	}


	void Nuklear::group_end () {
		nk_group_end (ctx);
	}


	void Nuklear::layout_row_dynamic (float height, int cols) {
		nk_layout_row_dynamic (ctx, height, cols);
	}


	void Nuklear::layout_row_static (float height, int item_width, int cols) {
		nk_layout_row_static (ctx, height, item_width, cols);
	}


	Nuklear::lua_float_map Nuklear::layout_space_bounds () {
		struct nk_rect nk_bounds = nk_layout_space_bounds (ctx);
		return lua_float_map (rect2map (nk_bounds));
	}


	Nuklear::lua_float_map Nuklear::widget_bounds () {
		struct nk_rect nk_bounds = nk_widget_bounds (ctx);
		return lua_float_map (rect2map (nk_bounds));
	}


	void Nuklear::label (const char *str, int flags) {
		nk_label (ctx, str, (nk_flags) flags);
	}


	void Nuklear::label_wrap (const char *str) {
		nk_label_wrap (ctx, str);
	}


	bool Nuklear::selectable_label (const char *str, int flags, bool selected) {
		int sel = (int) selected;
		nk_selectable_label (ctx, str, (nk_flags) flags, &sel);
		return (bool) sel;
	}


	bool Nuklear::button_label (const char *str) {
		return (bool) nk_button_label (ctx, str);
	}


	bool Nuklear::check_label (const char *str, bool active) {
		return (bool) nk_check_label (ctx, str, active);
	}


	int Nuklear::edit_string (int flags, const char *buffer) {
		return nk_edit_string_zero_terminated (ctx, flags, LF->buffer.get (buffer), LF->buffer.size (buffer),
		                                       nk_filter_default);
	}


	bool Nuklear::popup_begin (int type, const char *title, int flags, lua_float_map bounds) {
		return (bool) nk_popup_begin (ctx, (nk_popup_type) type, title, (nk_flags) flags, map2rect (bounds));
	}


	void Nuklear::popup_close () {
		nk_popup_close (ctx);
	}


	void Nuklear::popup_end () {
		nk_popup_end (ctx);
	}


	int Nuklear::combo (sol::as_table_t<vector_str> items, int selected, int item_height, float width, float height) {
		const vector_str &strings = items;
		std::vector<const char *> cstrings;
		for (auto &str : strings) cstrings.push_back (str.c_str ());
		return nk_combo (ctx, &cstrings[0], (int) cstrings.size (), selected, item_height, nk_vec2 (width, height));
	}


	int Nuklear::combo_separator (const char *items, const char *separator, int selected, int count, int item_height,
	                              float width, float height) {
		return nk_combo_separator (ctx, items, separator[0], selected, count, item_height, nk_vec2 (width, height));
	}


	void Nuklear::tooltip (const char *str) {
		nk_tooltip (ctx, str);
	}


	bool Nuklear::input_is_mouse_hovering_rect (lua_float_map bounds) {
		struct nk_rect nk_bounds = map2rect (bounds);
		return (bool) nk_input_is_mouse_hovering_rect (&ctx->input, nk_bounds);
	}


	void Nuklear::finish () {
		nk_end (ctx);
	}

}
