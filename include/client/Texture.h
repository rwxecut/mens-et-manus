#pragma once

#include "lib/glad.h"
#include <memory>

class Texture {
	GLuint id;
	int width, height;

public:
	Texture (const char *filename);
	~Texture ();

	void bind (GLuint unit);

	int w ();
	int h ();
	GLdouble aspect ();
};
using TexturePtr = std::unique_ptr<Texture>;
