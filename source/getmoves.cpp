#include <iostream>
#include "piece.h"
#include "piecetypes.h"
#include "chess.h"
#include "classifier.h"

using namespace std;

bool checkEnemy(Player* opponent, Position pos) {
    if (opponent->matrix[pos]) {
        return true;
    }
    return false;
}

std::vector<Move> Piece::getMoves(Player* player) {
    cout << "invalid thang" << endl;
    
    return {};
}

std::vector<Move> Pawn::getMoves(Player* player) {
    vector<Move> moves;

    int steps;

    (moved) ? steps = 1 : steps = 2;

    for (int step = 1; step <= steps; step++) {
        Position p(pos.col, pos.row + step * player->color);
        if (!p.inBounds() && player->matrix[p]) {
            return moves;
        }
        moves.push_back(Move(p));
    }

    // get enemies
    // add en peassantefafeav
    
    Position upLeftPos(pos.col - 1, pos.row + 1 * player->color);
    if (upLeftPos.inBounds() && checkEnemy(player->opponent, upLeftPos)) {
        moves.push_back(Move(upLeftPos, player->opponent->matrix[upLeftPos]));
    }

    Position upRightPos(pos.col + 1, pos.row + 1 * player->color);
    if (upRightPos.inBounds() && checkEnemy(player->opponent, upRightPos)) {
        moves.push_back(Move(upRightPos, player->opponent->matrix[upRightPos]));
    }

    return moves;
}

std::vector<Move> Knight::getMoves(Player* player) {
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
        if (move.pos.inBounds() && !player->matrix[move.pos]) {
            if (checkEnemy(player->opponent, move.pos)) {
                actualMoves.push_back(Move(move.pos, player->opponent->matrix[move.pos]));
            }
            actualMoves.push_back(Move(move.pos));
        }
    }

    return actualMoves;
}

std::vector<Move> Bishop::getMoves(Player* player) {
    vector<Move> moves;

    // check for collision/out of bounds etc

    // up left
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col - step, pos.row + step);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(p, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(p));
    }

    // up right
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col + step, pos.row + step);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(p, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(p));
    }

    // down left
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col - step, pos.row - step);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(p, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(p));
    }

    // down right
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col + step, pos.row - step);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(p, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(p));
    }

    return moves;
}

std::vector<Move> Rook::getMoves(Player* player) {
    vector<Move> moves;

    // up
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col, pos.row + step);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(p, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(p));
    }

    // down
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col, pos.row - step);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(p, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(p));
    }

    // left
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col - step, pos.row);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(p, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(p));
    }

    // right
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col + step, pos.row);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(p, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(p));
    }

    return moves;
}

std::vector<Move> Queen::getMoves(Player* player) {
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
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(p, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(p));
    }

    // up right
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col + step, pos.row + step);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(p, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(p));
    }

    // down left
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col - step, pos.row - step);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(p, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(p));
    }

    // down right
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col + step, pos.row - step);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(p, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(p));
    }

    // up
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col, pos.row + step);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(p, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(p));
    }

    // down
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col, pos.row - step);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(p, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(p));
    }

    // left
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col - step, pos.row);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(p, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(p));
    }

    // right
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col + step, pos.row);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(p, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(p));
    }

    return moves;
}

std::vector<Move> King::getMoves(Player* player) {
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
        if (move.pos.inBounds() && !player->matrix[move.pos]) {
            actualMoves.push_back(move);
        }
    }

    return actualMoves;
}


