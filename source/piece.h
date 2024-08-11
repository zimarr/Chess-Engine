#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <vector> //maybe set?
#include "move.h"
#include "position.h"
#include "classifier.h"

class Player;

class Piece {
    public:
        Piece() {}

        

        virtual std::vector<Move> getMoves(Player* player);

        Position pos;

        Color color;

        SDL_Texture *texture;

        void draw(Color turn, bool flipEnabled);

        bool moved = false;

        bool isKing = false;

        static SDL_Renderer *rend;
};

