#pragma once

int getXPos(char col);
int getYPos(int row);

template <typename P>
void drawPiece(SDL_Renderer *rend, P piece);