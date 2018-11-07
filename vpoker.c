/* Video Poker.  Simple SDL video poker prototype game my ekg98 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "cards.h"
#include "wccommon.h"

/* global constants aka defines */
#define WINDOW_WIDTH  1920
#define WINDOW_HEIGHT 1200

/* function prototypes */
int initsdl(void);
void closesdl(void);

/* global vpoker variables */
SDL_Window *mainWindow = NULL;
SDL_Surface *mainWindowSurface = NULL;
SDL_Event event;

/* main program */
int main()
{
  if(initsdl())  /* initialize sdl */
    return 1;
  else
  {
      while(event.type != SDL_QUIT)
      {

        SDL_PollEvent(&event);
      }
  }

  closesdl(); /* shut down sdl */
  return 0;
}

int initsdl(void)
{
  if(SDL_Init(SDL_INIT_VIDEO))
  {
    printf("SDL unable to initialize: %s", SDL_GetError());
    return 1;
  }

  mainWindow = SDL_CreateWindow("Video Poker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

  if(mainWindow == NULL)
  {
    printf("Window could not be created: %s", SDL_GetError());
    return 1;
  }
  else
    mainWindowSurface = SDL_GetWindowSurface(mainWindow);

  if(mainWindowSurface == NULL)
  {
    printf("Window surface could not be created: %s", SDL_GetError());
    return 1;
  }

  return 0;
}

void closesdl(void)
{
  SDL_FreeSurface(mainWindowSurface);
  SDL_DestroyWindow(mainWindow);
  SDL_Quit();
}
