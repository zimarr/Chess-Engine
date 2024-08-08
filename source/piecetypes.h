#pragma once

#include <SDL.h>
#include <vector>
#include "piece.h"
#include "move.h"

class Pawn : public Piece {
    public:
        Pawn(char  c, int r);

        std::vector<Move> getMoves() override;
};

class Knight : public Piece {
    public:
        Knight(char c, int r);

        std::vector<Move> getMoves() override;
};

class Bishop : public Piece {
    public:
        Bishop(char c, int r);

        std::vector<Move> getMoves() override;
};

class Rook : public Piece {
    public:
        Rook(char c, int r);

        std::vector<Move> getMoves() override;      
};

class Queen : public Piece {
    public:
        Queen(char c, int r);

        std::vector<Move> getMoves() override;      
};

class King : public Piece {
    public:
        King(char c, int r);

        std::vector<Move> getMoves() override;
};

