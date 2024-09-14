#include "text.h"

Text::Text(TTF_Font* font, SDL_Renderer* rend, int x_pos, int y_pos, const char *str) {
    x = x_pos;
    y = y_pos;
    SDL_Color textColor = {200, 200, 200};

    SDL_Surface* textSurface = TTF_RenderText_Blended(font, str, textColor);

    if (!textSurface) {
        std::cout << "ERROR" << SDL_GetError() << std::endl;
    }

    texture = SDL_CreateTextureFromSurface(rend, textSurface);
    SDL_FreeSurface(textSurface);

    if (!texture) {
        std::cout << "AAA " << std::endl;
    }

    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Text::draw(SDL_Renderer* rend) {
    SDL_Rect dstRect {x, y, width, height};
    SDL_RenderCopy(rend, texture, NULL, &dstRect);
}