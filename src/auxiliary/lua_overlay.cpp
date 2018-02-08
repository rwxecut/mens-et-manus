#include "auxiliary/lua_overlay.h"

namespace lua {

	void stackDump (lua_State *L) {
		int top = lua_gettop (L);
		printf ("Size: %d\n", top);

		for (int i = 1; i <= top; i++) {
			int t = lua_type (L, i);
			switch (t) {
				case LUA_TSTRING:
					printf ("string: '%s'\n", lua_tostring(L, i));
					break;
				case LUA_TBOOLEAN:
					printf ("boolean %s\n", lua_toboolean (L, i) ? "true" : "false");
					break;
				case LUA_TNUMBER:
					printf ("number: %g\n", lua_tonumber(L, i));
					break;
				default:
					printf ("%s\n", lua_typename (L, t));
					break;
			}
		}
		printf ("\n");
	}
}

