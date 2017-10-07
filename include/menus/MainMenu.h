#pragma once

#include <cstdint>
#include <GL/gl.h>
#include "geometry.h"

class MainMenu {
	friend class Window;
	bool active = false;

	void keyHandler (const uint8_t *keystates);
	void mousePositionHandler (size2d<int> screenSize, point2d<int> mousePos);
	void mouseScrollHandler (int32_t delta);
	void update (point2d<int> mousePos);
	void render ();

public:
	MainMenu ();
};
