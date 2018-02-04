#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>


class Texture {
	GLuint texID;

public:
	Texture ();
	bool load (const char *filename);
	void draw (const GLint *vertices, const GLint* texVertices);
	~Texture ();
};
