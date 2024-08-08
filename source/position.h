#pragma once

class Position {
    public:
        Position();
        Position(char c, int r);
        
        bool inBounds();

        char col;
        int row;
        


    private:

};