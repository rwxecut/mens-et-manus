#pragma once

#include "SDL_opengl.h"

class GameConfig {

	using std::string;
	static std::vector<string> assets_dirs = {
			string("./"),
			string("../assets/")
	};

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