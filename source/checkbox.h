#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "text.h"

struct CheckBox {
    int x, y, width, height;

    bool checked;

    Text text;
    
    void check();

    void click(int mousex, int mousey);

    bool isChecked();

    SDL_Texture *texture, *checkedtexture, *uncheckedtexture;

    CheckBox() {}
    CheckBox(int x_pos, int y_pos, const char *str, TTF_Font* font, SDL_Renderer* rend);

    void draw(SDL_Renderer *rend);
};