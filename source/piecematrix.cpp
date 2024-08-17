#include <algorithm>
#include <iostream>
#include "piecematrix.h"

Piece*& PieceMatrix::operator[](Position pos){
    return matrix[pos.col - 'A'][pos.row - 1];
}

void PieceMatrix::reset() {
    for (std::vector<Piece*>& row : matrix) {
        for (Piece*& piece : row) {
            piece = nullptr;
        }
    }
}


