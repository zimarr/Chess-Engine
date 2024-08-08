#include "piecematrix.h"

Piece*& PieceMatrix::operator[](Position pos){
    return matrix[pos.col - 'A'][pos.row];
}