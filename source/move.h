#pragma once

#include "position.h"

class Piece;

struct Move {
    Move(Position sp, Position np, Piece* p = nullptr, Piece* elim = nullptr) { // add elem param
        startPos = sp;
        nextPos = np;
        eliminate = elim;
        piece = p;
    }

    Position startPos;
    Position nextPos;
    Piece* eliminate = nullptr; // change to piece but error
    Piece* piece = nullptr;
};