#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

typedef GLuint GLtexture;

namespace sdl_gl {
	bool loadTexture (GLtexture *tex, const char *filename);
}
