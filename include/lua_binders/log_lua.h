#pragma once

#include "LuaFile.h"

namespace lua::bind {
	class Log {
		File *LF;

	public:
		Log (File *LF);

	/* Binded functions */
	private:
		static void write (const char* msg);
		static void warn (const char* msg);
		static void fatal (const char* msg);
	};
}
