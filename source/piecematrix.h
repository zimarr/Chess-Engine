#pragma once

#include <vector>
#include "piece.h"
#include "position.h"

struct PieceMatrix {
    std::vector<std::vector<Piece*>> matrix;

    PieceMatrix() : matrix(8, std::vector<Piece*>(8, nullptr)) {}

    Piece*& operator[](Position pos);

    void reset();
};