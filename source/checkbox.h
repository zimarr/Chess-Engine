#pragma once

#include <SDL.h>
#include "text.h"

struct CheckBox {
    int x, y, width, height;

    Text text;

    CheckBox(int x_pos, int y_pos, const char *str, TTF_Font* font, SDL_Renderer* rend);

    void draw(SDL_Renderer *rend);
};