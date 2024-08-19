#pragma once

#include "position.h"

class Piece;

class Move {
    public:
        Move(Position sp, Position np, Piece* p = nullptr, Piece* elim = nullptr) { // add elem param
            startPos = sp;
            nextPos = np;
            piece = p;
            eliminate = elim;
        }

        Move(Position kingsp, Position kingnp, Piece* king, Position rooksp, Position rooknp, Piece* rook) { // add elem param
            startPos = kingsp;
            nextPos = kingnp;
            piece = king;
            castleStartPos = rooksp;
            castleNextPos = rooknp;
            castle = rook;
        }

        Position startPos;
        Position nextPos;
        Piece* piece = nullptr;
        Piece* eliminate = nullptr;
        Position castleStartPos;
        Position castleNextPos;
        Piece* castle = nullptr;

        void make(Player* player);
        void undo(Player* player);
};