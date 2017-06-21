#include <SDL.h>
#include <cstdio>
#include "mouse.h"

#include "map.h"

extern SDL_Window *Window;

void mouseEventHandler (SDL_Event *event) {
	switch (event->type)
	{
		case SDL_MOUSEMOTION:
			char posstr[32];
			sprintf (posstr, "X: %d Y: %d", event->motion.x, event->motion.y);
			SDL_SetWindowTitle (Window, posstr);
			break;
		case SDL_MOUSEWHEEL:
			map::MouseScrollHandler (event->wheel.y);
			break;
	}
}

void mouseCommonHander ()
{
	map::MousePositionHandler ();
}
