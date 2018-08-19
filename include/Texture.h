#pragma once

#include "lib/glad.h"

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
