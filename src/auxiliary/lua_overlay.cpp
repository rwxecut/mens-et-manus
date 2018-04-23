#include "auxiliary/lua_overlay.h"
#include <sstream>
#include <cstring>

namespace lua {

	char *stackDump (lua_State *L) {
		std::ostringstream strStream;
		int top = lua_gettop (L);
		strStream << "Size of stack: " << top << "\n";

		for (int i = 1; i <= top; i++) {
			int t = lua_type (L, i);
			switch (t) {
				case LUA_TSTRING:
					strStream << "String: '" << lua_tostring (L, i) << "'\n";
					break;
				case LUA_TBOOLEAN:
					strStream << "Boolean: " << (lua_toboolean (L, i) ? "true" : "false") << "\n";
					break;
				case LUA_TNUMBER:
					strStream << "Number: " << lua_tonumber (L, i) << "\n";
					break;
				default:
					strStream << lua_typename (L, t) << "\n";
					break;
			}
		}

		std::string str = strStream.str ();
		char *cstr = new char[str.size () + 1];
		strcpy (cstr, str.c_str ());
		return cstr;
	}

}

