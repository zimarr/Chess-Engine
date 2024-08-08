#include <iostream>
#include "piece.h"
#include "piecetypes.h"
#include "chess.h"

using namespace std;

std::vector<Move> Piece::getMoves() {
    cout << "invalid thang" << endl;
    
    return {};
}

std::vector<Move> Pawn::getMoves() {
    vector<Move> moves;

    // only works for white
    // check for collision/out of bounds etc
    moves.push_back(Move(Position(pos.col, pos.row + 1)));
    moves.push_back(Move(Position(pos.col, pos.row + 2)));

    //experimental
    vector<Move> actualMoves;

    return moves;
}

std::vector<Move> Knight::getMoves() {
    vector<Move> moves;

    // check for collision/out of bounds etc
    moves.push_back(Move(Position(pos.col + 1, pos.row + 2)));
    moves.push_back(Move(Position(pos.col - 1, pos.row + 2)));
    moves.push_back(Move(Position(pos.col + 1, pos.row - 2)));
    moves.push_back(Move(Position(pos.col - 1, pos.row - 2)));
    moves.push_back(Move(Position(pos.col + 2, pos.row + 1)));
    moves.push_back(Move(Position(pos.col + 2, pos.row - 1)));
    moves.push_back(Move(Position(pos.col - 2, pos.row + 1)));
    moves.push_back(Move(Position(pos.col - 2, pos.row - 1)));

    //experimental
    vector<Move> actualMoves;

    for (Move move : moves) {
        if (move.pos.inBounds() && !Chess::whiteMatrix[move.pos]) {
            actualMoves.push_back(move);
        }
    }

    return actualMoves;
}

std::vector<Move> Bishop::getMoves() {
    vector<Move> moves;

    // check for collision/out of bounds etc

    // up left
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col - step, pos.row + step);
        if (!p.inBounds() || Chess::whiteMatrix[p]) {
            break;
        }
        moves.push_back(Move(p));
    }

    // up right
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col + step, pos.row + step);
        if (!p.inBounds() || Chess::whiteMatrix[p]) {
            break;
        }
        moves.push_back(Move(p));
    }

    // down left
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col - step, pos.row - step);
        if (!p.inBounds() || Chess::whiteMatrix[p]) {
            break;
        }
        moves.push_back(Move(p));
    }

    // down right
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col + step, pos.row - step);
        if (!p.inBounds() || Chess::whiteMatrix[p]) {
            break;
        }
        moves.push_back(Move(p));
    }

    return moves;
}

std::vector<Move> Rook::getMoves() {
    vector<Move> moves;

    // up
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col, pos.row + step);
        if (!p.inBounds() || Chess::whiteMatrix[p]) {
            break;
        }
        moves.push_back(Move(p));
    }

    // down
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col, pos.row - step);
        if (!p.inBounds() || Chess::whiteMatrix[p]) {
            break;
        }
        moves.push_back(Move(p));
    }

    // left
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col - step, pos.row);
        if (!p.inBounds() || Chess::whiteMatrix[p]) {
            break;
        }
        moves.push_back(Move(p));
    }

    // right
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col + step, pos.row);
        if (!p.inBounds() || Chess::whiteMatrix[p]) {
            break;
        }
        moves.push_back(Move(p));
    }

    return moves;
}

std::vector<Move> Queen::getMoves() {
    vector<Move> moves;

    // check for collision/out of bounds etc

    // keep this for now
    // for (int step = 1; step <= 8; step++) {
    //     moves.push_back(Move(Position(pos.col + step, pos.row + step)));
    //     moves.push_back(Move(Position(pos.col + step, pos.row - step)));
    //     moves.push_back(Move(Position(pos.col - step, pos.row + step)));
    //     moves.push_back(Move(Position(pos.col - step, pos.row - step)));
    // }

    // for (int step = 1; step <= 8; step++) {
    //     moves.push_back(Move(Position(pos.col + step, pos.row)));
    //     moves.push_back(Move(Position(pos.col - step, pos.row)));
    //     moves.push_back(Move(Position(pos.col, pos.row + step)));
    //     moves.push_back(Move(Position(pos.col, pos.row - step)));
    // }

    // up left
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col - step, pos.row + step);
        if (!p.inBounds() || Chess::whiteMatrix[p]) {
            break;
        }
        moves.push_back(Move(p));
    }

    // up right
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col + step, pos.row + step);
        if (!p.inBounds() || Chess::whiteMatrix[p]) {
            break;
        }
        moves.push_back(Move(p));
    }

    // down left
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col - step, pos.row - step);
        if (!p.inBounds() || Chess::whiteMatrix[p]) {
            break;
        }
        moves.push_back(Move(p));
    }

    // down right
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col + step, pos.row - step);
        if (!p.inBounds() || Chess::whiteMatrix[p]) {
            break;
        }
        moves.push_back(Move(p));
    }

    // up
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col, pos.row + step);
        if (!p.inBounds() || Chess::whiteMatrix[p]) {
            break;
        }
        moves.push_back(Move(p));
    }

    // down
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col, pos.row - step);
        if (!p.inBounds() || Chess::whiteMatrix[p]) {
            break;
        }
        moves.push_back(Move(p));
    }

    // left
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col - step, pos.row);
        if (!p.inBounds() || Chess::whiteMatrix[p]) {
            break;
        }
        moves.push_back(Move(p));
    }

    // right
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col + step, pos.row);
        if (!p.inBounds() || Chess::whiteMatrix[p]) {
            break;
        }
        moves.push_back(Move(p));
    }

    return moves;
}

std::vector<Move> King::getMoves() {
    vector<Move> moves;

    moves.push_back(Move(Position(pos.col + 1, pos.row + 1)));
    moves.push_back(Move(Position(pos.col + 1, pos.row - 1)));
    moves.push_back(Move(Position(pos.col - 1, pos.row + 1)));
    moves.push_back(Move(Position(pos.col - 1, pos.row - 1)));

    moves.push_back(Move(Position(pos.col + 1, pos.row)));
    moves.push_back(Move(Position(pos.col - 1, pos.row)));
    moves.push_back(Move(Position(pos.col, pos.row + 1)));
    moves.push_back(Move(Position(pos.col, pos.row - 1)));

    //experimental
    vector<Move> actualMoves;

    for (Move move : moves) {
        if (move.pos.inBounds() && !Chess::whiteMatrix[move.pos]) {
            actualMoves.push_back(move);
        }
    }

    return actualMoves;
}


