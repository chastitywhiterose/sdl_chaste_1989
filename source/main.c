#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_ttf.h"

/*variables that apply for any program I create that uses SDL2*/
int width=1280,height=720;
int loop=1;
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event e;

/*variables for SDL_image features*/
SDL_Texture *texture;
char filename[256];
int w,h;


/*variables for SDL_TTF features*/
char text[0x200];
TTF_Font *font=NULL;
int font_size=40;
char font_filename[256];
int renderstyle=TTF_STYLE_NORMAL;
SDL_Color font_color= {0,0,0,255};
SDL_Surface *text_surface;
SDL_Texture *text_texture;
SDL_Rect srcrect,dstrect;

#include "1989_image.h"
#include "1989_ttf.h"

int main(int argc, char **argv)
{
 if(SDL_Init(SDL_INIT_VIDEO))
 {
  printf( "SDL could not initialize! SDL_Error: %s\n",SDL_GetError());return -1;
 }
 window=SDL_CreateWindow("SDL Program",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_SHOWN );
 if(window==NULL){printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );return -1;}
 renderer = SDL_CreateRenderer(window,-1,0);
 if(renderer==NULL){printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );return -1;}

 printf("SDL Program Compiled Correctly\n");

 /*Draw a background pattern in case the image has transparency*/
 draw_background(renderer, width, height);

 /*fill entire screen with current draw color*/
 SDL_SetRenderDrawColor(renderer,255,255,255,255);
 SDL_RenderFillRect(renderer,NULL);

 /*flag_fill();*/
 
 /* Initialize the TTF library */
 if(TTF_Init() < 0)
 {
  SDL_Log("Couldn't initialize TTF: %s\n",SDL_GetError());
  SDL_Quit();
  return(2);
 }



 strcpy(font_filename,"font/DejaVuSansMono.ttf");
 strcpy(font_filename,"font/editundo.ttf");

 font = TTF_OpenFont(font_filename, font_size);
 if (font == NULL)
 {
  SDL_Log("Couldn't load %d pt font from %s: %s\n",
                    font_size, font_filename, SDL_GetError());

 }
 else
 {
  printf("font file '%s'loaded\n",font_filename);
 }

 TTF_SetFontStyle(font, renderstyle);
 /*TTF_SetFontKerning(font, 1);*/

 strcpy(text,"Chastity White Rose");

font_color.r=0;
font_color.g=0;
font_color.b=0;

text_test();

 TTF_CloseFont(font);
 TTF_Quit();

 SDL_DestroyRenderer(renderer);
 SDL_DestroyWindow(window);
 SDL_Quit();
 return 0;
}
