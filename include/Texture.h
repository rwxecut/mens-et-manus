#pragma once

#include "lib/glad.h"

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
