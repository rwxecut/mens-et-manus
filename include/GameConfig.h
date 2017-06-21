#pragma once

#include "SDL_opengl.h"

class GameConfig {

public:

	GameConfig (char const *fname);
	GameConfig (GameConfig const &gc);

	bool valid () const;

	struct screen_s {
		GLint width = 0;
		GLint height = 0;
	} screen;

	struct video_s {
		struct cam_s {
			GLdouble fov = 90.0f;
			struct pos_s {
				GLdouble x = 0.0f;
				GLdouble y = 0.0f;
				GLdouble z = 0.0f;
			} pos;
		} cam;
	} video;
};