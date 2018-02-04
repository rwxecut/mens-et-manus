#include "auxiliary/sdl_gl_overlay.h"


bool Texture::load (const char *filename) {
	SDL_Surface *image = IMG_Load (filename);
	if (!image)
		return false;
	glGenTextures (1, &texID);
	glBindTexture (GL_TEXTURE_2D, texID);
	int mode = (image->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D (GL_TEXTURE_2D, 0, mode, image->w, image->h, 0, mode, GL_UNSIGNED_BYTE, image->pixels);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	SDL_FreeSurface (image);
	return true;
}


void Texture::draw (const GLint *vertices, const GLint *texVertices) {
	glBindTexture (GL_TEXTURE_2D, texID);
	glEnableClientState (GL_VERTEX_ARRAY);
	glEnableClientState (GL_TEXTURE_COORD_ARRAY);
	glVertexPointer (2, GL_INT, 0, vertices);
	glTexCoordPointer (2, GL_INT, 0, texVertices);
	glDrawArrays (GL_QUADS, 0, 4);
	glDisableClientState (GL_TEXTURE_COORD_ARRAY);
	glDisableClientState (GL_VERTEX_ARRAY);
}


Texture::Texture () {};


Texture::~Texture () {
	glDeleteTextures (1, &texID);
}

