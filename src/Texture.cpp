#include "Texture.h"


Texture::Texture (const char *filename) {
	SDL_Surface *image = IMG_Load (filename);
	if (!image)
		fatalError ("Can't load texture: %s", filename);
	glGenTextures (1, &texID);
	glBindTexture (GL_TEXTURE_2D, texID);
	GLenum mode = (image->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D (GL_TEXTURE_2D, 0, mode, image->w, image->h, 0, mode, GL_UNSIGNED_BYTE, image->pixels);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	width = image->w;
	height = image->h;

	SDL_FreeSurface (image);
	logger.write ("Texture loaded: %s", filename);
};


Texture::~Texture () {
	glDeleteTextures (1, &texID);
}


void Texture::draw (GLenum mode, GLsizei count, const GLfloat *vertex, const GLfloat *texCoord) {
	glBindTexture (GL_TEXTURE_2D, texID);
	glVertexPointer (3, GL_FLOAT, 0, vertex);
	glTexCoordPointer (2, GL_FLOAT, 0, texCoord);
	glDrawArrays (mode, 0, count);
}


void Texture::stateDraw (GLenum mode, GLsizei count, const GLfloat *vertex, const GLfloat *texCoord) {
	glEnableClientState (GL_VERTEX_ARRAY);
	glEnableClientState (GL_TEXTURE_COORD_ARRAY);
	draw (mode, count, vertex, texCoord);
	glDisableClientState (GL_TEXTURE_COORD_ARRAY);
	glDisableClientState (GL_VERTEX_ARRAY);
}


int Texture::w () { return width; }


int Texture::h () { return height; }


GLdouble Texture::aspect () { return (GLdouble) width / (GLdouble) height; }
