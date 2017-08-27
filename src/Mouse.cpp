#include "Mouse.h"

const int Mouse::moveMapArea = 40;

void Mouse::positionHandler (Cam *cam, int scrWidth, int scrHeight) {
	SDL_GetMouseState (&pos.x, &pos.y);
	// @formatter:off
	cam->accelerate ((pos.x < moveMapArea),
					 (pos.x > scrWidth - moveMapArea),
					 (pos.y < moveMapArea),
					 (pos.y > scrHeight - moveMapArea));
	// @formatter:on
}


void Mouse::scrollHandler (Cam *cam, int32_t delta) {
	cam->zoom (delta);
}
