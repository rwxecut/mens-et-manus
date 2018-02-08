#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "auxiliary/exceptions.h"
#include "Logger.h"


class Texture {
	GLuint texID;

public:
	Texture (const char *filename);
	void draw (GLenum mode, GLsizei count, const GLfloat *vertex, const GLfloat *texCoord);
	void stateDraw (GLenum mode, GLsizei count, const GLfloat *vertex, const GLfloat *texCoord);
	~Texture ();
};
