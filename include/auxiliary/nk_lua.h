#pragma once

#include "LuaFile.h"
#include "nuklear/nuklear_common.h"

namespace lua::nk {
	void init (LuaFile *LF);
	void run (LuaFile *LF, nk_context *nkContext);

	// Binded functions
	bool begin (const char *title, float x, float y, float w, float h, int flags);
	void layout_row_dynamic (float height, int cols);
	void layout_row_static (float height, int item_width, int cols);
	bool button_label (const char *title);
	bool finish ();
}
