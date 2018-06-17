#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "auxiliary/errors.h"
#include "Logger.h"


class Texture {
	GLuint texID;
	int width, height;

public:
	Texture (const char *filename);
	~Texture ();

	void draw (GLenum mode, GLsizei count, const GLfloat *vertex, const GLfloat *texCoord);
	void stateDraw (GLenum mode, GLsizei count, const GLfloat *vertex, const GLfloat *texCoord);

	int w ();
	int h ();
	GLdouble aspect ();
};
