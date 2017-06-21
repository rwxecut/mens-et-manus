#pragma once

struct {
	int x, y;
} mouse;

void mouseEventHandler (SDL_Event *event);
void mouseCommonHander ();