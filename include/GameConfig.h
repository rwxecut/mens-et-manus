#pragma once

#include "SDL_opengl.h"
#include <vector>
#include <string>

using std::string;

class GameConfig {
	static std::vector<string> const assets_dirs;

public:

	struct screen_s {
		GLint width;
		GLint height;
	} screen;

	struct files_s {
		std::string assets_dir = "";
	} files;

	struct video_s {
		GLfloat fov;
	} video;

	GameConfig (string fname);
	GameConfig (GameConfig const &gc);

	bool valid () const;
};