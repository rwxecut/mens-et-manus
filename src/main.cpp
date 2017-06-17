#include <SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int init (SDL_Window **window, SDL_Surface **screenSurface);

int main (int argc, char *args[])
{
  SDL_Window *window = NULL;
  SDL_Surface *screenSurface = NULL;

  if (!init(&window, &screenSurface))
    SDL_Quit();

  SDL_FillRect (screenSurface, NULL, SDL_MapRGB (screenSurface->format, 0xFF, 0xFF, 0xFF));
  SDL_UpdateWindowSurface (window);
  SDL_Delay (2000);

  SDL_DestroyWindow (window);
  SDL_Quit ();

  return 0;
}

int init (SDL_Window **window, SDL_Surface **screenSurface)
{
  if (SDL_Init (SDL_INIT_VIDEO) < 0)
  {
    printf ("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }
  else
  {
    *window = SDL_CreateWindow ("Mens et Manus", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (*window == NULL)
    {
      printf ("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      return 1;
    }
  }
  *screenSurface = SDL_GetWindowSurface (*window);
  return 0;
}
