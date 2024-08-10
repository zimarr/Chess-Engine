#pragma once

#include <vector>
#include "piece.h"
#include "piecematrix.h"
#include "classifier.h"

class Player {
    public:
        Player() {}
        Player(Color c) : color(c) {}
        
        std::vector<Piece*> pieces;

        Piece* selecting = nullptr;
        bool playing = false;

        PieceMatrix matrix;

        Player* opponent;

        Color color;

    private:

};