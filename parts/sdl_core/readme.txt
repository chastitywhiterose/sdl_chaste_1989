This folder contains a program that only creates a window and draws a color to it. It will close if you click the X or press Esc.

It may seem pointless but this is the start of a basic program. This one uses the SDL_Renderer for drawing rather than the old surface method. If you are curious about the way that works using surfaces and no renderer, the full source code of such a program is below.


#include <stdio.h>
#include <SDL.h>
int width=1280,height=720;
int loop=1;
SDL_Window *window;
SDL_Surface *surface;
SDL_Event e;
int main(int argc, char **argv)
{
 if(SDL_Init(SDL_INIT_VIDEO))
 {
  printf( "SDL could not initialize! SDL_Error: %s\n",SDL_GetError());return -1;
 }
 window=SDL_CreateWindow("SDL Program",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_SHOWN );
 if(window==NULL){printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );return -1;}
 surface = SDL_GetWindowSurface( window ); /*get surface for this window*/
 SDL_FillRect(surface,NULL,0xFF00FF);
 SDL_UpdateWindowSurface(window);
 printf("SDL Program Compiled Correctly\n");
 while(loop)
 {
  while(SDL_PollEvent(&e))
  {
   if(e.type == SDL_QUIT){loop=0;}
   if(e.type == SDL_KEYUP)
   {
    if(e.key.keysym.sym==SDLK_ESCAPE){loop=0;}
   }
  }
 }
 SDL_DestroyWindow(window);
 SDL_Quit();
 return 0;
}

This program and more are available on my SDL_Blank repository.

https://github.com/chastitywhiterose/SDL_Blank/
