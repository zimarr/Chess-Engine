#include <algorithm>
#include "piecematrix.h"

Piece*& PieceMatrix::operator[](Position pos){
    return matrix[pos.col - 'A'][pos.row];
}

void PieceMatrix::reset() {
    for (auto& row : matrix) {
        std::fill(row.begin(), row.end(), nullptr);
    }
}


