#pragma once

#include "geometry.h"
#include "nuklear/nuklear_common.h"

struct WindowState {
	struct {
		size2d<int> screenSize;
		GLdouble fpsInterval;
	} attrib;
	point2d<int> mousePos;
};
