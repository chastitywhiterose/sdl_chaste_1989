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
int font_size=200;
char font_filename[256];
int renderstyle=TTF_STYLE_NORMAL;
SDL_Color font_color= {0,0,0,255};
SDL_Surface *text_surface;
SDL_Texture *text_texture;
SDL_Rect srcrect,dstrect;

/* Draw a Gimpish background pattern to show transparency in the image */
static void draw_background(SDL_Renderer *renderer, int w, int h)
{
    SDL_Color col[2] = {
        { 0x66, 0x66, 0x66, 0xff },
        { 0x99, 0x99, 0x99, 0xff },
    };
    int i, x, y;
    SDL_Rect rect;
    const int dx = 8, dy = 8;

    rect.w = dx;
    rect.h = dy;
    for (y = 0; y < h; y += dy) {
        for (x = 0; x < w; x += dx) {
            /* use an 8x8 checkerboard pattern */
            i = (((x ^ y) >> 3) & 1);
            SDL_SetRenderDrawColor(renderer, col[i].r, col[i].g, col[i].b, col[i].a);

            rect.x = x;
            rect.y = y;
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

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

 SDL_SetRenderDrawColor(renderer,0,255,0,255);
 SDL_RenderFillRect(renderer,NULL);

 printf("SDL Program Compiled Correctly\n");

 /*Draw a background pattern in case the image has transparency*/
 draw_background(renderer, width, height);

 /* Open the image file */

 strcpy(filename,"./bitmap/Chastity_Progress_Flag.png");
 texture = IMG_LoadTexture(renderer, filename);
 if (!texture)
 {
  SDL_Log("Couldn't load %s: %s\n", filename, SDL_GetError());
 }
 else
 {
  SDL_QueryTexture(texture, NULL, NULL, &w, &h);
  printf("Image '%s' loaded\n",filename);
  printf("Texture dimensions w=%d,h=%d\n",w,h);
 }

 /* Display the image */
 SDL_RenderCopy(renderer, texture, NULL, NULL);

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

 strcpy(text,"Chastity");

 TTF_SizeText(font, text, &w, &h);

 printf("To render string\n'%s'\nwill be size w=%d,h=%d\n",text,w,h);

font_color.r=255;
font_color.g=255;
font_color.b=255;

 text_surface=TTF_RenderText_Solid(font, text, font_color);

 if(text_surface != NULL)
 {
  text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
  SDL_FreeSurface(text_surface);
 }

 srcrect.x=0;
 srcrect.y=0;
 srcrect.w=w;
 srcrect.h=h;

 dstrect=srcrect;
 dstrect.x=400;
 dstrect.y=280;

 SDL_RenderCopy(renderer, text_texture, &srcrect, &dstrect);

 SDL_RenderPresent(renderer);

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

 TTF_CloseFont(font);
 TTF_Quit();

 SDL_DestroyRenderer(renderer);
 SDL_DestroyWindow(window);
 SDL_Quit();
 return 0;
}
