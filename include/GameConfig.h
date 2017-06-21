#pragma once

#include "SDL_opengl.h"

class GameConfig {

	struct screen_s
	{
		GLint width;
		GLint height;
	} screen_;

public:

	GameConfig (char const *fname);
	GameConfig (GameConfig const &gc);

	bool valid () const;

	const screen_s &screen = screen_;

};