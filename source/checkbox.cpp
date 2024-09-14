#include "checkbox.h"

CheckBox::CheckBox(int x_pos, int y_pos, const char *str, TTF_Font* font, SDL_Renderer* rend) {
    x = x_pos;
    y = y_pos;
    text = Text(font, rend, x_pos + 20, y_pos, str);
}

void CheckBox::draw(SDL_Renderer *rend) {
    SDL_SetRenderDrawColor(rend, 23, 92, 41, 255);

    SDL_Rect rect{x, y, 50, 50};
    SDL_RenderFillRect(rend, &rect);
    
    text.draw(rend);
}