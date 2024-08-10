#include "piece.h"



void Piece::draw(Color turn, bool flipEnabled) {
    int rgb_val = (color + 1) / 2 * 255;
    int rgb_val_difference = (color + 1) / 2 * 200;

    SDL_SetTextureColorMod(texture, 55 + rgb_val_difference, 30 + rgb_val_difference, 0 + rgb_val_difference);

    SDL_Rect rect{pos.getXPos(turn, flipEnabled), pos.getYPos(turn, flipEnabled), 100, 100};
    SDL_RenderCopy(rend, texture, NULL, &rect);

    SDL_SetTextureColorMod(texture, 255, 0, 0);
}

SDL_Renderer *Piece::rend = nullptr;