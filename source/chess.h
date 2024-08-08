#pragma once

#include <vector>
#include "piece.h"
#include "player.h"
#include "piecematrix.h"

class Chess {
    public:
        Chess();
        ~Chess() {};
        
        void update();

        void draw(SDL_Renderer *rend);

        void initPieces(SDL_Renderer *rend);

        void drawMoves();

        void mouseClick(SDL_Event e);
        void mouseRelease(SDL_Event e);
        Piece* getClickedPiece(int x, int y);

        static PieceMatrix whiteMatrix;

    // private:
        std::vector<Move> moves;

        Player white;
        Player black;
};