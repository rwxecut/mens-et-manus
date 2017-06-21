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
			GLfloat fov = 90.0f;
			struct pos_s {
				GLfloat x = 0.0f;
				GLfloat y = 0.0f;
				GLfloat z = 0.0f;
			} pos;
		} cam;
	} video;
};