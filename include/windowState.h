#pragma once

#include "geometry.h"
#include "nuklear/nuklear_common.h"

struct WindowState {
	struct {
		size2d<int> screenSize;
	} attrib;
	point2d<int> mousePos;
	struct nk_context **nkContext;
};
