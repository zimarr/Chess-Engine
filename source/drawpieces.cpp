#include <SDL.h>
#include "drawpieces.h"
#include "piece.h"

// int getXPos(char col) {
//     return (col -  'A') * 100;
// }

// int getYPos(int row) {
//     return 800 - row * 100;
// }

// template <typename P>
// void drawPiece<>(SDL_Renderer *rend, P piece) {
//     SDL_Rect rect{getXPos(piece.pos.col), getYPos(piece.pos.row), 100, 100};    
//     SDL_RenderCopy(rend, piece.texture, NULL, &rect);
// }