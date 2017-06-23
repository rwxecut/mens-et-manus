#pragma once

#include <SDL_keycode.h>

namespace map {
	void Init ();
	void Draw ();
	void Update ();
	void KeyHandler (SDL_Keycode key);
	void MousePositionHandler ();
	void MouseScrollHandler (int32_t delta);
}
