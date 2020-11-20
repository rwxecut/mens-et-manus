#include "client/Texture.h"
#include <SDL.h>
#include <SDL_image.h>
#include "engine/Logger.h"
#include "auxiliary/errors.h"


Texture::Texture (const char *filename) {
	SDL_Surface *image = IMG_Load (filename);
	if (!image) {
		fatalError ("Can't load texture %s: %s", filename, IMG_GetError());
	} else {
		glGenTextures (1, &id);
		glBindTexture (GL_TEXTURE_2D, id);
		GLenum mode = (image->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
		glTexImage2D (GL_TEXTURE_2D, 0, mode, image->w, image->h, 0, mode, GL_UNSIGNED_BYTE, image->pixels);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		width = image->w;
		height = image->h;
	}

	logger.write ("Texture loaded: %s", filename);
	SDL_FreeSurface (image);
};


Texture::~Texture () {
	glDeleteTextures (1, &id);
}


void Texture::bind (GLuint unit) {
	glActiveTexture (GL_TEXTURE0 + unit);
	glBindTexture (GL_TEXTURE_2D, id);
}


int Texture::w () { return width; }


int Texture::h () { return height; }


GLdouble Texture::aspect () { return (GLdouble) width / (GLdouble) height; }
