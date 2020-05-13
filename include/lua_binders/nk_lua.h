#pragma once

#include <map>
#include <string>
#include <vector>
#include "LuaFile.h"
#include "lib/nuklear/nuklear_common.h"

namespace lua {
	class NuklearBinding {
		LuaFile *LF;
		static nk_context *ctx;

	public:
		NuklearBinding (LuaFile *LF);
		static void init (nk_context *nkContext);

	/* Binded functions */
	private:
		typedef std::vector<std::string> vector_str;
		typedef std::map<std::string, float> float_map;
		typedef sol::as_table_t<float_map> lua_float_map;
		static struct nk_rect map2rect (float_map const &map);
		static float_map rect2map (struct nk_rect const &rect);

		bool begin (const char *title, lua_float_map bounds, int flags);
		lua_float_map window_get_bounds ();
		bool group_begin (const char *title, int flags);
		void group_end ();
		void layout_row_dynamic (float height, int cols);
		void layout_row_static (float height, int item_width, int cols);
		lua_float_map layout_space_bounds ();
		lua_float_map widget_bounds ();
		void label (const char *str, int flags);
		void label_wrap (const char *str);
		bool selectable_label (const char *str, int flags, bool selected);
		bool button_label (const char *str);
		bool check_label (const char *str, bool active);
		int edit_string (int flags, char* str, int max);
		bool popup_begin (int type, const char *title, int flags, lua_float_map bounds);
		void popup_close ();
		void popup_end ();
		int combo (sol::as_table_t<vector_str> items, int selected, int item_height, float width, float height);
		int combo_separator (const char *items, const char *separator, int selected, int count, int item_height,
		                     float width, float height);
		void tooltip (const char *str);
		bool input_is_mouse_hovering_rect (lua_float_map bounds);
		void finish ();
	};
}
