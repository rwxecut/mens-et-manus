#pragma once

#include <type_traits>

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

namespace lua {

	template<typename T>
	inline T getTableField (lua_State *L, const char *field) {
		static_assert (std::is_same<T, int>::value || std::is_same<T, double>::value,
		               "Only int and double are allowed");
		lua_pushstring (L, field);
		lua_gettable (L, -2);
		T value;
		if (std::is_same<T, int>::value)
			value = (int) luaL_checkinteger (L, -1);
		if (std::is_same<T, double>::value)
			value = (double) luaL_checknumber (L, -1);
		lua_pop(L, 1);
		return value;
	}

	void stackDump (lua_State *L);
}
