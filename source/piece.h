#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <stdexcept>
#include "move.h"
#include "position.h"
#include "classifier.h"

class Player;

class Piece {
    public:
        Piece() {}

        

        virtual std::vector<Move> getMoves(Player* player);

        virtual Piece* clone() const { throw std::runtime_error("can't clone raw piece"); }

        Position pos;

        Color color;

        SDL_Texture *texture;

        void draw(Color turn, bool flipEnabled);

        bool moved = false;

        bool isKing = false;
        bool isRook = false;
        bool isPawn = false;

        int value = 0;

        static SDL_Renderer *rend;
};

