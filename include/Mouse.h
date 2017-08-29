#pragma once

#include <SDL.h>
#include "Cam.h"
#include "geometry.h"

class Mouse {

	static const int moveMapArea;

public:
	point2d<int> pos;

	void positionHandler (Cam *cam, int scrWidth, int scrHeight);
	void scrollHandler (Cam *cam, int32_t delta);
};