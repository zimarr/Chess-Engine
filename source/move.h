#pragma once

#include "position.h"
#include "piece.h"

struct Move {
    Move(Position np) { // add elem param
        pos = np;
    }

    Position pos;
    int *eliminate = nullptr; // change to piece but error
};