#pragma once

#include "LuaFile.h"
#include "nuklear/nuklear_common.h"

namespace lua::nk {
	void bind (LuaFile *LF);
	void run (LuaFile *LF, nk_context *nkContext);
}
