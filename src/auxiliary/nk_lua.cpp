#include "auxiliary/nk_lua.h"


namespace lua::nk {

	nk_context *ctx;


	void init (LuaFile *LF) {
		// Bind functions
		luaL_Reg funclist[] = {
				lua_addBindFunc (begin),
				lua_addBindFunc (layout_row_dynamic),
				lua_addBindFunc (layout_row_static),
				lua_addBindFunc (button_label),
				lua_addBindFunc (finish),
				{NULL, NULL}
		};
		luaL_newlib (LF->L, funclist);

		// Export constants
		field<int> keys[] = {
				lua_addExportKey (NK_WINDOW_BORDER),
				lua_addExportKey (NK_WINDOW_MOVABLE),
				lua_addExportKey (NK_WINDOW_SCALABLE),
				lua_addExportKey (NK_WINDOW_CLOSABLE),
				lua_addExportKey (NK_WINDOW_MINIMIZABLE),
				lua_addExportKey (NK_WINDOW_NO_SCROLLBAR),
				lua_addExportKey (NK_WINDOW_TITLE),
				lua_addExportKey (NK_WINDOW_SCROLL_AUTO_HIDE),
				lua_addExportKey (NK_WINDOW_BACKGROUND),
				lua_addExportKey (NK_WINDOW_SCALE_LEFT),
				lua_addExportKey (NK_WINDOW_NO_INPUT),
				{NULL, 0}
		};
		setTableFields (LF->L, keys);
		lua_setglobal (LF->L, "gui");
	}


	void run (LuaFile *LF, nk_context *nkContext) {
		lua::nk::ctx = nkContext;
		LF->run ("render");
	}


	// Binded functions

	lua_cfunc (begin) {
		lua_pushboolean (L, nk_begin (ctx,
		                              luaL_checkstring (L, 1),
		                              nk_rect (lua_arg_float (L, 2),
		                                       lua_arg_float (L, 3),
		                                       lua_arg_float (L, 4),
		                                       lua_arg_float (L, 5)),
		                              (nk_flags) lua_arg_int (L, 6)));
		return 1;
	}


	lua_cfunc (layout_row_dynamic) {
		nk_layout_row_dynamic (ctx,
		                       lua_arg_float (L, 1),
		                       lua_arg_int (L, 2));
		return 0;
	}


	lua_cfunc (layout_row_static) {
		nk_layout_row_static (ctx,
		                      lua_arg_float (L, 1),
		                      lua_arg_int (L, 2),
		                      lua_arg_int (L, 3));
		return 0;
	}


	lua_cfunc (button_label) {
		lua_pushboolean (L, nk_button_label (ctx,
		                                     luaL_checkstring (L, 1)));
		return 1;
	}


	lua_cfunc (finish) {
		nk_end (ctx);
		return 0;
	}

}
