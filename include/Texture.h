#pragma once

#include <stdexcept>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>


class Texture {
	GLuint texID;

public:
	Texture (const char *filename);
	void draw (const GLint *vertices, const GLint* texVertices);
	~Texture ();
};
