/*
1989_graphics.h

this header file is meant to contain all the functions which write things to the screen
*/

void draw_stats_1989()
{
 int line=1;
 text_x=font_size;

 ttf_print("Chaste Tris 1989",font_size*line++,0);

 sprintf(text,"Score %d",score);
 ttf_print(text,text_x,font_size*line++);

 sprintf(text,"Lines %d",lines_cleared_total);
 ttf_print(text,text_x,font_size*line++);

 sprintf(text,"This %c",main_block.id);
 ttf_print(text,text_x,font_size*line++);

 sprintf(text,"Hold %c",hold_block.id);
 ttf_print(text,text_x,font_size*line++);

 sprintf(text,"Move %d",moves);
 ttf_print(text,text_x,font_size*line++);

 sprintf(text,"B2B %d",back_to_back);
 ttf_print(text,text_x,font_size*line++);

 sprintf(text,"Combo %d",combo);
 ttf_print(text,text_x,font_size*line++);

  time(&time1);
  
  seconds=time1-time0; /*subtract current time from start time to get seconds since game started*/

  minutes=seconds/60;
  seconds%=60;
  hours=minutes/60;
  minutes%=60;
  
  sprintf(text,"Time %d:%02d:%02d",hours,minutes,seconds);
  ttf_print(text,text_x,font_size*line++);

  /*sprintf(text,"Frame %d",frame);
  ttf_print(text,text_x,font_size*line++);*/
}

/*a function pointer that points to whichever function I currently use to draw the game stats to the screen*/
void (*stats_func)()=draw_stats_1989;
 
/*more global variables to be defined before game loop function*/
int border_size;

/*
this is a function which is called by main after window is created. It contains the game loop.
*/
void sdl_chastetris()
{
 /*int pixel,r,g,b;*/
 int x=0,y=0;

 /*setup the grid display*/
 block_size=height/grid_height;
 grid_offset_x=(width-(20/2*block_size))/2; /*formula for grid to center of screen*/
 border_size=block_size;

 printf("block_size==%d\n",block_size);
  
 spawn_block();


 /*first empty the grid*/
 y=0;
 while(y<grid_height)
 {
  x=0;
  while(x<grid_width)
  {
   main_grid.array[x+y*grid_width]=empty_color;
   x+=1;
  }
  y+=1;
 }

 delay=1000/fps;
 
 /*get time before the game starts using standard library time function*/
 time(&time0);

 /*
  an optional step before the game loop but a very awesome one
  initialize the spinning polygon that will be drawn each frame
 */

 init_polygon();
 main_polygon.radius=height*11/64;
 main_polygon.sides=4;
 main_polygon.step=1;

 main_polygon.color.r=0;
 main_polygon.color.g=0;
 main_polygon.color.b=0;

 main_polygon.cx=width*11/64;
 main_polygon.cy=height*50/64;

 
 loop=1;
  /* Loop until the user closes the window */
 while(loop)
 {
  sdl_time = SDL_GetTicks();
  sdl_time1 = sdl_time+delay;

  SDL_SetRenderDrawColor(renderer,255,255,255,255);
  SDL_RenderClear(renderer);

 /*make backup of entire grid*/
  temp_grid=main_grid;

  /*draw block onto temp grid at it's current location*/
  y=0;
  while(y<max_block_width)
  {
   x=0;
   while(x<max_block_width)
   {
    if(main_block.array[x+y*max_block_width]!=0)
    {
     if(temp_grid.array[main_block.x+x+(main_block.y+y)*grid_width]!=0)
     {
      printf("Error: Block in Way\n");

      /*because a collision has occurred. We will restore everything back to the way it was before block was moved.*/

      break;
     }
     else
     {
      main_color=main_block.color;

      temp_grid.array[main_block.x+x+(main_block.y+y)*grid_width]=main_color;
     }
    }
    x+=1;
   }
   y+=1;
  }



/*display the tetris grid*/
show_grid();

/*show the polygon just for fun*/
chaste_polygon_draw_star();
/*chaste_polygon_draw_star_lines();*/
main_polygon.radians+=PI/180;


 /*draw the boundary walls*/

/*
 set up the rectangle structure with the needed data to square the walls
*/

 SDL_SetRenderDrawColor(renderer,0,0,0,255);

 rect.x=grid_offset_x-border_size;
 rect.y=0*block_size;
 rect.w=border_size;
 rect.h=height;

SDL_RenderFillRect(renderer,&rect);

 rect.x=grid_offset_x+grid_width*block_size;
SDL_RenderFillRect(renderer,&rect);


 /*end of drawing code for grid*/

 stats_func();
 /*draw_input();*/


 /*optionally, get input from another file instead of keyboard if I have this enabled.*/
  next_file_input();

 /*test for events and only process if they exist*/
 while(SDL_PollEvent(&e))
 {
  keyboard();
 }

 SDL_RenderPresent(renderer);

 /*time loop used to slow the game down so users can see it*/
 while(sdl_time<sdl_time1)
 {
  sdl_time=SDL_GetTicks();
 }

 frame++;

 }

}






