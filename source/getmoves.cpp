#include <iostream>
#include "piece.h"
#include "piecetypes.h"
#include "chess.h"
#include "classifier.h"

using namespace std;

bool isValidMoveInCheck(Player* player, Move move) {
    Position originalPos = move.piece->pos;

    player->matrix[move.piece->pos] = nullptr;
    move.piece->pos = move.pos;
    player->matrix[move.pos] = move.piece;

    if (move.eliminate) {
        for (int i = 0; i < player->opponent->pieces.size(); i++) {
            if (player->opponent->pieces[i] == move.eliminate) {
                player->opponent->pieces.erase(player->opponent->pieces.begin() + i);
            }
        }

        player->opponent->matrix[move.eliminate->pos] = nullptr;
    }    

    for (Piece* piece : player->opponent->pieces) {
        std::vector<Move> moves = piece->getMoves(player->opponent);
        for (Move& enemyMove : moves) {
            if (enemyMove.eliminate) {
                if (enemyMove.eliminate->isKing) {
                    move.piece->pos = originalPos;
                    player->matrix[move.piece->pos] = move.piece;
                    player->matrix[move.pos] = nullptr;

                    if (move.eliminate) {
                        player->opponent->pieces.push_back(move.eliminate);
                        player->opponent->matrix[move.eliminate->pos] = move.eliminate;
                    } 

                    cout << "ay gang wsg" << endl;
                    return false;
                }
            }
        }
    }

    move.piece->pos = originalPos;
    player->matrix[move.piece->pos] = move.piece;
    player->matrix[move.pos] = nullptr;

    if (move.eliminate) {
        player->opponent->pieces.push_back(move.eliminate);
        player->opponent->matrix[move.eliminate->pos] = move.eliminate;
    } 
    
    return true;
}

bool checkEnemy(Player* opponent, Position pos) {
    if (opponent->matrix[pos] != nullptr) {
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
        if (!p.inBounds() || player->matrix[p] || player->opponent->matrix[p]) {
            break;
        }

        moves.push_back(Move(p, this));   
    }

    // get enemies
    // add en peassantefafeav
    
    Position upLeftPos(pos.col - 1, pos.row + 1 * player->color);
    if (upLeftPos.inBounds() && checkEnemy(player->opponent, upLeftPos)) {
        moves.push_back(Move(upLeftPos, this, player->opponent->matrix[upLeftPos]));
    }

    Position upRightPos(pos.col + 1, pos.row + 1 * player->color);
    if (upRightPos.inBounds() && checkEnemy(player->opponent, upRightPos)) {
        moves.push_back(Move(upRightPos, this, player->opponent->matrix[upRightPos]));
    }

    if (player->inCheck) {
        std::vector<Move> actualMoves;
    
        for (Move& move : moves) {
            if (isValidMoveInCheck(player, move)) {
                actualMoves.push_back(move);
            }
        }

        return actualMoves;
    }

    return moves;
}

std::vector<Move> Knight::getMoves(Player* player) {
    vector<Move> moves;

    // check for collision/out of bounds etc
    moves.push_back(Move(Position(pos.col + 1, pos.row + 2), this));
    moves.push_back(Move(Position(pos.col - 1, pos.row + 2), this));
    moves.push_back(Move(Position(pos.col + 1, pos.row - 2), this));
    moves.push_back(Move(Position(pos.col - 1, pos.row - 2), this));
    moves.push_back(Move(Position(pos.col + 2, pos.row + 1), this));
    moves.push_back(Move(Position(pos.col + 2, pos.row - 1), this));
    moves.push_back(Move(Position(pos.col - 2, pos.row + 1), this));
    moves.push_back(Move(Position(pos.col - 2, pos.row - 1), this));

    //experimental
    vector<Move> checkedMoves;

    for (Move move : moves) {
        if (move.pos.inBounds() && !player->matrix[move.pos]) {
            if (checkEnemy(player->opponent, move.pos)) {
                checkedMoves.push_back(Move(move.pos, this, player->opponent->matrix[move.pos]));
            } else {
                checkedMoves.push_back(Move(move.pos, this));
            }
        }
    }

    if (player->inCheck) {
        std::vector<Move> actualMoves;
    
        for (Move& move : checkedMoves) {
            if (isValidMoveInCheck(player, move)) {
                actualMoves.push_back(move);
            }
        }

        return actualMoves;
    }

    return checkedMoves;
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
            moves.push_back(Move(p, this, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(p, this));
    }

    // up right
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col + step, pos.row + step);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(p, this, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(p, this));
    }

    // down left
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col - step, pos.row - step);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(p, this, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(p, this));
    }

    // down right
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col + step, pos.row - step);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(p, this, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(p, this));
    }

    if (player->inCheck) {
        std::vector<Move> actualMoves;
    
        for (Move& move : moves) {
            if (isValidMoveInCheck(player, move)) {
                actualMoves.push_back(move);
            }
        }

        return actualMoves;
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
            moves.push_back(Move(p, this, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(p, this));
    }

    // down
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col, pos.row - step);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(p, this, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(p, this));
    }

    // left
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col - step, pos.row);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(p, this, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(p, this));
    }

    // right
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col + step, pos.row);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(p, this, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(p, this));
    }

    if (player->inCheck) {
        std::vector<Move> actualMoves;
    
        for (Move& move : moves) {
            if (isValidMoveInCheck(player, move)) {
                actualMoves.push_back(move);
            }
        }

        return actualMoves;
    }

    return moves;
}

std::vector<Move> Queen::getMoves(Player* player) {
    vector<Move> moves;

    // up left
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col - step, pos.row + step);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(p, this, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(p, this));
    }

    // up right
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col + step, pos.row + step);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(p, this, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(p, this));
    }

    // down left
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col - step, pos.row - step);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(p, this, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(p, this));
    }

    // down right
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col + step, pos.row - step);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(p, this, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(p, this));
    }

    // up
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col, pos.row + step);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(p, this, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(p, this));
    }

    // down
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col, pos.row - step);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(p, this, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(p, this));
    }

    // left
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col - step, pos.row);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(p, this, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(p, this));
    }

    // right
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col + step, pos.row);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(p, this, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(p, this));
    }

    if (player->inCheck) {
        std::vector<Move> actualMoves;
    
        for (Move& move : moves) {
            if (isValidMoveInCheck(player, move)) {
                actualMoves.push_back(move);
            }
        }

        return actualMoves;
    }

    return moves;
}

std::vector<Move> King::getMoves(Player* player) {
    vector<Move> moves;

    moves.push_back(Move(Position(pos.col + 1, pos.row + 1), this));
    moves.push_back(Move(Position(pos.col + 1, pos.row - 1), this));
    moves.push_back(Move(Position(pos.col - 1, pos.row + 1), this));
    moves.push_back(Move(Position(pos.col - 1, pos.row - 1), this));

    moves.push_back(Move(Position(pos.col + 1, pos.row), this));
    moves.push_back(Move(Position(pos.col - 1, pos.row), this));
    moves.push_back(Move(Position(pos.col, pos.row + 1), this));
    moves.push_back(Move(Position(pos.col, pos.row - 1), this));

    //experimental
    vector<Move> checkedMoves;

    for (Move move : moves) {
        if (move.pos.inBounds() && !player->matrix[move.pos]) {
            if (checkEnemy(player->opponent, move.pos)) {
                checkedMoves.push_back(Move(move.pos, this, player->opponent->matrix[move.pos]));
            } else {
                checkedMoves.push_back(Move(move.pos, this));
            }
        }
    }

    if (player->inCheck) {
        std::vector<Move> actualMoves;
    
        for (Move& move : checkedMoves) {
            if (isValidMoveInCheck(player, move)) {
                actualMoves.push_back(move);
            }
        }

        return actualMoves;
    }

    return checkedMoves;
}


