#pragma once

#include "LuaFile.h"
#include "nuklear/nuklear_common.h"

namespace lua::nk {
	void init (nk_context *nkContext);
	void bind (LuaFile *LF);
	void run (LuaFile *LF);
}
