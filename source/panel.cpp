#include "panel.h"



Panel::Panel(int w, int h) {
    width = w;
    height = h;

    font = TTF_OpenFont("./res/fonts/open_sans.ttf", 13);
    
    if (!font) {
        std::cout << "ERRRROR" << SDL_GetError() << std::endl; return;
    }
}

void Panel::addText(int x, int y, SDL_Renderer* rend, const char *str) {
    texts.push_back(new Text(font, rend, x, y, str));
}

void Panel::draw(SDL_Renderer* rend) {
    SDL_SetRenderDrawColor(rend, 166, 255, 221, 255);
    
    SDL_Rect rect{0, 0, width, height};
    SDL_RenderFillRect(rend, &rect);
    
    for (Text* text : texts) {
        text->draw(rend);
    }
}

void Panel::initTexts(SDL_Renderer* rend) {
    addText(10, 10, rend, "GRRRRRRRRRAAAAAAA");
}