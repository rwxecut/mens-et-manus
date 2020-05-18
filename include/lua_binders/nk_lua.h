#pragma once

#include <map>
#include <string>
#include <vector>
#include "LuaFile.h"
#include "lib/nuklear/nuklear_common.h"

namespace lua::bind {
	class Nuklear {
		File *LF;
		static nk_context *ctx;

	public:
		Nuklear (File *LF);
		static void init (nk_context *nkContext);

		/* Binded functions */
	private:
		typedef std::vector<std::string> vector_str;
		typedef std::map<std::string, float> float_map;
		typedef sol::as_table_t<float_map> lua_float_map;
		static struct nk_rect map2rect (float_map const &map);
		static float_map rect2map (struct nk_rect const &rect);

		static bool begin (const char *title, lua_float_map bounds, int flags);
		static lua_float_map window_get_bounds ();
		static bool group_begin (const char *title, int flags);
		static void group_end ();
		static void layout_row_dynamic (float height, int cols);
		static void layout_row_static (float height, int item_width, int cols);
		static lua_float_map layout_space_bounds ();
		static lua_float_map widget_bounds ();
		static void label (const char *str, int flags);
		static void label_wrap (const char *str);
		static bool selectable_label (const char *str, int flags, bool selected);
		static bool button_label (const char *str);
		static bool check_label (const char *str, bool active);
		static int edit_string (int flags, char *str, int max);
		static bool popup_begin (int type, const char *title, int flags, lua_float_map bounds);
		static void popup_close ();
		static void popup_end ();
		static int combo (sol::as_table_t<vector_str> items, int selected, int item_height, float width, float height);
		static int combo_separator (const char *items, const char *separator, int selected, int count, int item_height,
		                            float width, float height);
		static void tooltip (const char *str);
		static bool input_is_mouse_hovering_rect (lua_float_map bounds);
		static void finish ();
	};
}
