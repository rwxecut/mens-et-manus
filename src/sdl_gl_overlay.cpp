#include "sdl_gl_overlay.h"

bool sdl_gl::loadTexture (GLtexture *tex, const char *filename) {
	SDL_Surface *image = IMG_Load (filename);
	if (!image)
		return false;
	glGenTextures (1, tex);
	glBindTexture (GL_TEXTURE_2D, *tex);
	int mode = (image->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D (GL_TEXTURE_2D, 0, mode, image->w, image->h, 0, mode, GL_UNSIGNED_BYTE, image->pixels);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	SDL_FreeSurface (image);
	return true;
}
