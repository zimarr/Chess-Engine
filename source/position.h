#pragma once

#include "classifier.h"

class Player;
class Piece;

class Position {
    public:
        Position();
        Position(char c, int r);

        int getXPos(Color turn, bool flipEnabled);
        int getYPos(Color turn, bool flipEnabled);
        
        bool inBounds();

        char col;
        int row;
        
        bool isAttacked(Player* enemy);

        bool operator==(const Position& other) const;

    private:

};