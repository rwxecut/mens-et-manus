#include <SDL.h>
#include <stdio.h>

#include "main_menu.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool initSDL (SDL_Window **window, SDL_Surface **screenSurface);
void final (SDL_Window **window);

int main (int argc, char *args[])
{
  SDL_Window *window = NULL;
  SDL_Surface *screenSurface = NULL;

  if (!initSDL (&window, &screenSurface))
    final (&window);

  mainMenu_Draw(window, screenSurface);
  SDL_Delay (2000);

  final (&window);
  return 0;
}

bool initSDL (SDL_Window **window, SDL_Surface **screenSurface)
{
  if (SDL_Init (SDL_INIT_VIDEO) < 0)
  {
    printf ("SDL could not initialize! SDL_Error: %s\n", SDL_GetError ());
    return false;
  }
  *window = SDL_CreateWindow ("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                             SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (*window == NULL)
  {
    printf ("Window could not be created! SDL_Error: %s\n", SDL_GetError ());
    return false;
  }
  *screenSurface = SDL_GetWindowSurface (*window);
  return true;
}

void final (SDL_Window **window)
{
    if (*window)
        SDL_DestroyWindow (*window);
    SDL_Quit ();
}