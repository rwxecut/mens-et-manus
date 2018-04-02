#pragma once

#include <type_traits>

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#define lua_addBindFunc(name) {#name, name}
#define lua_addExportKey(key) {#key, (int) key}
#define lua_cfunc(name) int name (lua_State *L)
#define lua_arg_int(L, n) (int) luaL_checkinteger (L, n)
#define lua_arg_float(L, n) (float) luaL_checknumber (L, n)


namespace lua {

	void stackDump (lua_State *L);


	template<typename T>
	struct field {
		const char *name;
		T value;
	};


	template<typename T>
	inline void setTableField (lua_State *L, const char *field, T value) {
		static_assert (std::is_same<T, int>::value || std::is_same<T, double>::value,
		               "Only int and double are allowed");
		if (std::is_same<T, int>::value)
			lua_pushinteger (L, value);
		if (std::is_same<T, double>::value)
			lua_pushnumber (L, value);
		lua_setfield (L, -2, field);
	}


	template<typename T>
	void setTableFields (lua_State *L, field<T> *fields) {
		static_assert (std::is_same<T, int>::value || std::is_same<T, double>::value,
		               "Only int and double are allowed");
		int i = 0;
		while (fields[i].name) {
			setTableField<T> (L, fields[i].name, fields[i].value);
			i++;
		}
	}
}
