#pragma once

#include "position.h"

class Piece;

struct Move {
    Move(Position np, Piece* p = nullptr, Piece* elim = nullptr) { // add elem param
        pos = np;
        eliminate = elim;
        piece = p;
    }

    Position pos;
    Piece* eliminate = nullptr; // change to piece but error
    Piece* piece = nullptr;
};