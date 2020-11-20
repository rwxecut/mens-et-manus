#pragma once

#include "engine/LuaFile.h"

#define BIND_EXPORT_METHOD(table, binder, field) {table[#field] = &binder::field;}
#define BIND_EXPORT_CONSTANT(table, field) {table[#field] = sol::var(field);}

namespace lua::bind {
	class Bind {
	protected:
		File *LF = nullptr;
		Bind (File *LF) : LF(LF) {}
	};
}
