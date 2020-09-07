#pragma once

#include "LuaFile.h"

namespace lua::bind {
	class Bind {
	protected:
		File *LF = nullptr;
		Bind (File *LF) : LF(LF) {}
	};
}
