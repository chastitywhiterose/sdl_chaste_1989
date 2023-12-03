

/* Draw a Gimpish background pattern to show transparency in the image */
void draw_background(SDL_Renderer *renderer, int w, int h)
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


/*
fill the screen with the progress flag or whichever other image is used instead
this is a testing function which loads an image, prints details about it, draws it to screen, and then frees the memory
it won't be used in the game but parts of it should be copied and reused for displaying other images.
*/

void flag_fill()
{

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

 /*free the memory and delete the texture*/
 SDL_DestroyTexture(texture);

}