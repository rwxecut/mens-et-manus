#pragma once

#include "geometry.h"

struct WindowState {
	struct {
		size2d<int> screenSize;
	} attrib;
	point2d<int> mousePos;
};
