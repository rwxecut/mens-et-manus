#pragma once

#include "SDL_opengl.h"
#include <vector>
#include <string>

using std::string;

class GameConfig {
	static std::vector<string> const assets_dirs;
	static string const config_fname;

public:

	struct files_s {
		std::string assets_dir = "";
	} files;

	struct screen_s {
		GLint width = 0;
		GLint height = 0;
	} screen;

	struct video_s {
		struct cam_s {
			GLdouble fov = 90.0;
			GLdouble renderDistance = 1000.0;
			struct pos_s {
				GLdouble x = 0.0;
				GLdouble y = 0.0;
				GLdouble z = 0.0;
			} pos;
		} cam;
	} video;

	GameConfig ();
	GameConfig (GameConfig const &gc);

	bool valid () const;
};