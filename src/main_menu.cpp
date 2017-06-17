#include <SDL.h>

void mainMenu_Draw (SDL_Window *window, SDL_Surface *screenSurface)
{
    SDL_FillRect (screenSurface, NULL, SDL_MapRGB (screenSurface->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface (window);
}
