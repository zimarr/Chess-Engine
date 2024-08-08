#include "position.h"

Position::Position() {
    col = 'A';
    row = 0;
}

Position::Position(char c, int r) {
    col = c;
    row = r;
}

bool Position::inBounds() {
    return col >= 'A' && col <= 'H' && row >= 1 && row <= 8;
}