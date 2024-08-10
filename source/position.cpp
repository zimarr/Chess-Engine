#include "position.h"

Position::Position() {
    col = 'A';
    row = 0;
}

Position::Position(char c, int r) {
    col = c;
    row = r;
}

int Position::getXPos(Color turn, bool flipEnabled) {
    if (!flipEnabled | turn == WHITE) {
        return (col - 'A') * 100;
    } else {
        return (7 - (col - 'A')) * 100;
    }
}

int Position::getYPos(Color turn, bool flipEnabled) {
    if (!flipEnabled | turn == WHITE) {
        return (8 - row) * 100;
    } else {
        return (row - 1) * 100;
    }
}

bool Position::inBounds() {
    return col >= 'A' && col <= 'H' && row >= 1 && row <= 8;
}