#pragma once

#include "lua_binders/bind_lua.h"

namespace lua::bind {
	class Log : public Bind {
	public:
		Log (File *LF);

	/* Binded functions */
	private:
		static void write (const char* msg);
		static void warn (const char* msg);
		static void fatal (const char* msg);
	};
}
