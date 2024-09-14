#include "panel.h"



Panel::Panel(int w, int h) {
    width = 0;
    height = h;

    open = false;

    font = TTF_OpenFont("./res/fonts/open_sans.ttf", 20);
    
    if (!font) {
        std::cout << "ERRRROR" << SDL_GetError() << std::endl; return;
    }
}

void Panel::addText(int x, int y, SDL_Renderer* rend, const char *str) {
    texts.push_back(new Text(font, rend, x, y, str));
}

void Panel::addCheckBox(int x, int y, SDL_Renderer* rend, const char *str) {
    checkboxes.push_back(new CheckBox(x, y, str, font, rend));
}

void Panel::draw(SDL_Renderer* rend) {
    if (!open) {
        return;
    }
    
    SDL_SetRenderDrawColor(rend, 50, 50, 50, 255);
    
    SDL_Rect rect{0, 0, width, height};
    SDL_RenderFillRect(rend, &rect);
    
    for (Text* text : texts) {
        text->draw(rend);
    }

    for (CheckBox* check : checkboxes) {
        check->draw(rend);
    }
}

void Panel::checkAllBoxes(int mousex, int mousey) {
    for (CheckBox* check : checkboxes) {
        check->click(mousex, mousey);
    }
}

void Panel::initTexts(SDL_Renderer* rend) {
    flip = new CheckBox(10, 100, "Flip board", font, rend);

    show_moves = new CheckBox(10, 140, "Show possible moves", font, rend);

    show_points = new CheckBox(10, 180, "Show points metere - WPI", font, rend);

    checkboxes.push_back(flip);
    checkboxes.push_back(show_moves);
    checkboxes.push_back(show_points);
}

void Panel::setOpen() {
    open = !open;

    if (open) {
        width = 300;
    } else {
        width = 0;
    }
}

bool Panel::isOpen() {
    return open;
}

int Panel::getWidth() {
    return width;
}

int Panel::getHeight() {
    return height;
}