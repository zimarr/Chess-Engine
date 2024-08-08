#include "piece.h"

int Piece::getXPos() {
    return (pos.col -  'A') * 100;
}

int Piece::getYPos() {
    return (8 - pos.row) * 100;
}

void Piece::draw() {
    SDL_Rect rect{getXPos(), getYPos(), 100, 100};
    SDL_RenderCopy(rend, texture, NULL, &rect);
}

SDL_Renderer *Piece::rend = nullptr;