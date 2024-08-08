#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <vector> //maybe set?
#include "move.h"
#include "position.h"

class Piece {
    public:
        Piece() {};

        int getXPos();
        int getYPos();

        virtual std::vector<Move> getMoves();

        Position pos;

        SDL_Texture *texture;

        void draw();

        static SDL_Renderer *rend;
};

