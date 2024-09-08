#pragma once

#include <SDL.h>
#include <vector>
#include "piece.h"
#include "player.h"
#include "move.h"
#include "classifier.h"

class Pawn : public Piece {
    public:
        Pawn(char  c, int r, Color clr);

        std::vector<Move> getMoves(Player* player) override;

        Pawn* clone() const override {
            return new Pawn(*this);
        }
};

class Knight : public Piece {
    public:
        Knight(char c, int r, Color clr);

        std::vector<Move> getMoves(Player* player) override;

        Knight* clone() const override {
            return new Knight(*this);
        }
};

class Bishop : public Piece {
    public:
        Bishop(char c, int r, Color clr);

        std::vector<Move> getMoves(Player* player) override;

        Bishop* clone() const override {
            return new Bishop(*this);
        }
};

class Rook : public Piece {
    public:
        Rook(char c, int r, Color clr);

        std::vector<Move> getMoves(Player* player) override;

        Rook* clone() const override {
            return new Rook(*this);
        }
};

class Queen : public Piece {
    public:
        Queen(char c, int r, Color clr);

        std::vector<Move> getMoves(Player* player) override;

        Queen* clone() const override {
            return new Queen(*this);
        }   
};

class King : public Piece {
    public:
        King(char c, int r, Color clr);

        std::vector<Move> getMoves(Player* player) override;

        King* clone() const override {
            return new King(*this);
        }
};

