#pragma once

#include <vector>
#include "piece.h"
#include "player.h"
#include "piecematrix.h"
#include "classifier.h"

class Chess {
    public:
        Chess();
        ~Chess() {};
        
        void update();

        void draw(SDL_Renderer *rend, int left_padding, bool show_moves);

        void initPieces(SDL_Renderer *rend);
    
        void drawMoves();

        void checkForCheck(Player* player);

        void mouseClick(SDL_Event e);
        void mouseRelease(SDL_Event e);
        Piece* getClickedPiece(int x, int y);
        Position getClickedPosition(int x, int y);
        void switchTurns();

    // private:
        std::vector<Move> moves;

        Player white;
        Player black;

        bool flipEnabled;

        Player* play;
};