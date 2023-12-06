#include <stdio.h>
#include <time.h>
#include <math.h>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_ttf.h"
#include <SDL_mixer.h>

/*variables that apply for any program I create that uses SDL2*/
int width=1280,height=720;
int loop=1;
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event e;

/*variables for SDL_image features*/
SDL_Texture *texture;
char filename[256];
int x,y,w,h;


/*variables for SDL_ttf features*/
char text[0x200];
TTF_Font *font=NULL;
int font_size=40;
char font_filename[256];
int renderstyle=TTF_STYLE_NORMAL;
SDL_Color font_color= {0,0,0,255};
SDL_Surface *text_surface;
SDL_Texture *text_texture;
SDL_Rect srcrect,dstrect;



/*variables for SDL_mixture features*/

int songs=3,song_index=0,music_is_on=0;
char *music_files[]=
{
 "music/Tetris_Gift_from_Moscow_OC_ReMix.mp3",
 "music/04 Tetris (feat. Cement City).mp3",
 "music/01 Tetris (feat. Wish on the Beat).mp3"
};

Mix_Chunk *music[3]; /*chunks the music is loaded into*/


#include "1989_image.h"
#include "1989_ttf.h"
#include "1989_mixer.h"


/*variables applicable to my Tetris game*/

int fps=60; /*frames per second*/

int frame=0,lastframe=0,delay,framelimit=1; /*only used for animation demos*/
time_t time0,time1;
int seconds,minutes,hours; /*to keep track of time*/
int sdl_time,sdl_time1;

char gamename[256];
int blocks_used=7;
SDL_Rect rect;

char text[0x200];
char movetext[256],move_id;
int text_x; /*the x position of where text will go*/

FILE *fp; /*to save a file of moves played*/
char filename[256]; /*name of move log file*/
FILE *fp_input; /*file to get input from instead of the keyboard*/

#include "1989_chastetris.h"
#include "1989_gamesave.h"

#include "1989_grid_draw.h"
#include "1989_input.h"
#include "1989_polygon.h"
#include "1989_graphics.h"

int main(int argc, char **argv)
{
 if(SDL_Init(SDL_INIT_VIDEO))
 {
  printf( "SDL could not initialize! SDL_Error: %s\n",SDL_GetError());return -1;
 }
 window=SDL_CreateWindow("Chaste Tris 1989",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_SHOWN );
 if(window==NULL){printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );return -1;}
 renderer = SDL_CreateRenderer(window,-1,0);
 if(renderer==NULL){printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );return -1;}

 printf("SDL Program Compiled Correctly\n");

 /*Draw a background pattern in case the image has transparency*/
 draw_background(renderer, width, height);

 /*fill entire screen with current draw color*/
 SDL_SetRenderDrawColor(renderer,255,255,255,255);
 SDL_RenderClear(renderer);

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

 /*text_test();*/


/*
 After testing the image and ttf features, we need to initialize all audio this is the section to handle it. First all the music is loaded. Then the mix_test or game is played. At the end, the music is freed and shut down.
*/

chaste_audio_init(); /*get the audio device ready*/

 /*load all songs*/
 x=0;
 while(x<songs)
 {
  music[x]=chaste_audio_load(music_files[x]);
  x++;
 }


 /*mix_test();*/

 song_index=0;
 chaste_audio_play(music[song_index]);


 sprintf(filename,"imovelog.txt");
 fp_input=fopen(filename,"rb+");
 if(fp_input==NULL)
 {
  printf("Failed to open input file \"%s\".\n",filename);
  printf("This is not an error. It just means input is keyboard only. \"%s\".\n",filename);
 }
 else
 {
  printf("input file \"%s\" is opened.\n",filename);
  printf("Will read commands from this file before keyboard. \"%s\".\n",filename);
 }


 image_fill("./bitmap/ChastityWhiteRose_1280x720.png");
 sdl_chastetris();
 image_fill("./bitmap/Chastity_Progress_Flag.png");

  /*
  After the game ends, we will attempt to save the movelog to a file.
  Keeping the movelog in memory and only writing at the end speeds up the program and simplifies things.
 */
 
  /*open the file to record moves*/
 sprintf(filename,"omovelog.txt");
 fp=fopen(filename,"wb+");
 if(fp==NULL){printf("Failed to create file \"%s\".\n",filename);}
 else
 {
  x=0;
  while(x<moves)
  {
   /*printf("%d %c\n",x,move_log[x]);*/
   fputc(move_log[x],fp);
   x++;
  }
 }

 if(fp!=NULL){fclose(fp);}
 if(fp_input!=NULL){fclose(fp_input);}



  /*unload and free the music*/
 x=0;
 while(x<songs)
 {
  if(music[x]!=NULL)
  {
   Mix_FreeChunk(music[x]);
   music[x]=NULL;
  }
  x++;
 }
 
  if (audio_open)
  {
   Mix_CloseAudio();
   audio_open = 0;
  }
  /*end of music closing section*/



 TTF_CloseFont(font);
 TTF_Quit();

 SDL_DestroyRenderer(renderer);
 SDL_DestroyWindow(window);
 SDL_Quit();
 return 0;
}
