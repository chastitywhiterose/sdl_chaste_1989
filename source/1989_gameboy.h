/*
 obviously, the 1989 edition of Chaste Tris is based off of the Gameboy Tetris released in 1989
 That's where the title comes from and also why the grid is 18 blocks high in this version instead of 20.

 This source file has a special purpose: to load the images for the blocks exactly as they would have looked on the Gameboy.
*/

SDL_Texture *block_texture[7];

char *gb_blocks[]=
{
 "./bitmap/gb/i.png",
 "./bitmap/gb/t.png",
 "./bitmap/gb/z.png",
 "./bitmap/gb/j.png",
 "./bitmap/gb/o.png",
 "./bitmap/gb/l.png",
 "./bitmap/gb/s.png",
};



void show_grid_gameboy()
{
 int pixel,r,g,b;
 int x=0,y=0;
 int texture_index=0;

 y=0;
 while(y<grid_height)
 {
  x=0;
  while(x<grid_width)
  {
   pixel=temp_grid.array[x+y*grid_width];

   if(pixel!=0) /*only draw if something is there*/
   {
    r=(pixel&0xFF0000)>>16;
    g=(pixel&0x00FF00)>>8;
    b=(pixel&0x0000FF);

    SDL_SetRenderDrawColor(renderer,r,g,b,255);

    srcrect.x=0;
    srcrect.y=0;
    srcrect.w=8;
    srcrect.h=8;

    dstrect.x=grid_offset_x+x*block_size;
    dstrect.y=y*block_size;
    dstrect.w=block_size;
    dstrect.h=block_size;

    /*SDL_RenderFillRect(renderer,&dstrect);*/

   /*use the color of the pixel as a switch to select the right block index*/
   switch(pixel)
   {
    case 0x00FFFF:
     texture_index=0;
    break;
    case 0xFF00FF:
     texture_index=1;
    break;
    case 0xFF0000:
     texture_index=2;
    break;
    case 0x0000FF:
     texture_index=3;
    break;
    case 0xFFFF00:
     texture_index=4;
    break;
    case 0xFF7F00:
     texture_index=5;
    break;
    case 0x00FF00:
     texture_index=6;
    break;
   }

    SDL_RenderCopy(renderer, block_texture[texture_index], &srcrect, &dstrect);
   }

   x+=1;
  }
  y+=1;
 }
}




void load_gameboy_blocks()
{
 y=0;
 x=0;
 while(x<7)
 {

 block_texture[x] = IMG_LoadTexture(renderer, gb_blocks[x]);
 if(!block_texture[x])
 {
  SDL_Log("Couldn't load %s: %s\n", gb_blocks[x], SDL_GetError());
 }
 else
 {
  SDL_QueryTexture(block_texture[x], NULL, NULL, &w, &h);
  printf("Image '%s' loaded\n",gb_blocks[x]);
  /*printf("Texture dimensions w=%d,h=%d\n",w,h);*/
  y++;
 }

 printf("blocks loaded = %d\n",y);

 x++;
}

if(y==7)
{
 show_grid=show_grid_gameboy;
}

}