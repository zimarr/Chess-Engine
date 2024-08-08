#pragma once

#include <vector>
#include "piece.h"

class Player {
    public:
        std::vector<Piece*> pieces;

        Piece* selecting = nullptr;
        bool playing = false;

    private:

};