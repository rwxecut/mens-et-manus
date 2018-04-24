#pragma once

#include "auxiliary/geometry.h"
#include "nuklear/nuklear_common.h"

struct WindowState {
	size2d<int> screenSize;
	nk_context *nkContext;
};
