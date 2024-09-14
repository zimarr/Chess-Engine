#include "checkbox.h"
#include <iostream>

CheckBox::CheckBox(int x_pos, int y_pos, const char *str, TTF_Font* font, SDL_Renderer* rend) {
    x = x_pos;
    y = y_pos;

    checked = false;

    uncheckedtexture = IMG_LoadTexture(rend, "./res/checkbox.png");

    if (!(uncheckedtexture)) {
        std::cout << "ERROR" << std::endl;
    }

    checkedtexture = IMG_LoadTexture(rend, "./res/checkedbox.png");

    if (!(checkedtexture)) {
        std::cout << "ERROR" << std::endl;
    }

    texture = uncheckedtexture;

    text = Text(font, rend, x_pos + 30, y_pos - 3, str);
}

void CheckBox::check() {
    checked = !checked;

    checked ? texture = checkedtexture : texture = uncheckedtexture;
}

void CheckBox::click(int mousex, int mousey) {
    if (mousex < x + 25 && mousex > x && mousey < y + 25 && mousey > y) {
        check();
    }
}

bool CheckBox::isChecked() {
    return checked;
}

void CheckBox::draw(SDL_Renderer *rend) {
    // SDL_SetRenderDrawColor(rend, 23, 92, 41, 255);

    // SDL_Rect outerrect{x, y, 25, 25};
    // SDL_RenderFillRect(rend, &outerrect);
    
    SDL_Rect rect{x, y, 25, 25};
    SDL_RenderCopy(rend, texture, NULL, &rect);

    // SDL_SetRenderDrawColor(rend, 71, 255, 119, 255);
    
    // SDL_Rect innerrect{x + 2, y + 2, 21, 21};
    // SDL_RenderFillRect(rend, &innerrect);

    text.draw(rend);
}