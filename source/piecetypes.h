#pragma once

#include <SDL.h>
#include <vector>
#include "piece.h"
#include "player.h"
#include "move.h"

class Pawn : public Piece {
    public:
        Pawn(char  c, int r);

        std::vector<Move> getMoves(Player* player) override;
};

class Knight : public Piece {
    public:
        Knight(char c, int r);

        std::vector<Move> getMoves(Player* player) override;
};

class Bishop : public Piece {
    public:
        Bishop(char c, int r);

        std::vector<Move> getMoves(Player* player) override;
};

class Rook : public Piece {
    public:
        Rook(char c, int r);

        std::vector<Move> getMoves(Player* player) override;      
};

class Queen : public Piece {
    public:
        Queen(char c, int r);

        std::vector<Move> getMoves(Player* player) override;      
};

class King : public Piece {
    public:
        King(char c, int r);

        std::vector<Move> getMoves(Player* player) override;
};

