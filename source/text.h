#include <SDL.h>
#include <SDL_ttf.h>

#include <iostream>



struct Text {
    Text(TTF_Font* font, SDL_Renderer* rend, int x_pos, int y_pos, const char *str);

    void draw(SDL_Renderer* rend);
    
    int x, y, width, height;

    SDL_Texture* texture;
};