#pragma once

#include <vector>
#include "Mod.h"
#include "LuaFile.h"

namespace lua::modlist {
	void init (ModList *modList);
	void bind (LuaFile *LF);
}
