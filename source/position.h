#pragma once

#include "classifier.h"

class Position {
    public:
        Position();
        Position(char c, int r);

        int getXPos(Color turn, bool flipEnabled);
        int getYPos(Color turn, bool flipEnabled);
        
        bool inBounds();

        char col;
        int row;
        


    private:

};