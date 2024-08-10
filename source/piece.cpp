#include "piece.h"



void Piece::draw(Color turn, bool flipEnabled) {
    SDL_Rect rect{pos.getXPos(turn, flipEnabled), pos.getYPos(turn, flipEnabled), 100, 100};
    SDL_RenderCopy(rend, texture, NULL, &rect);
}

SDL_Renderer *Piece::rend = nullptr;