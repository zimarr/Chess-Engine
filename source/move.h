#pragma once

#include "position.h"

class Piece;

struct Move {
    Move(Position np, Piece* elim = nullptr) { // add elem param
        pos = np;
        eliminate = elim;
    }

    Position pos;
    Piece* eliminate = nullptr; // change to piece but error
};