void ttf_print(char *text,int x,int y)
{
 TTF_SizeText(font, text, &w, &h);
 /*printf("To render string\n'%s'\nwill be size w=%d,h=%d\n",text,w,h);*/
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
 dstrect.x=x;
 dstrect.y=y;

 SDL_RenderCopy(renderer, text_texture, &srcrect, &dstrect);

 /*free the memory and delete the texture*/
 SDL_DestroyTexture(text_texture);
}




void text_test()
{

 ttf_print("Chastity White Rose",0,0);
 ttf_print("The Vegan Virgin",0,font_size*1);

 SDL_RenderPresent(renderer);

 loop=1;
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

}