#include <iostream>
#include "piece.h"
#include "piecetypes.h"
#include "chess.h"
#include "classifier.h"

using namespace std;

int sign(int a) {
    return (a < 0) ? -1 : 1;
}

void checkCheckmate(Player* player) {
    player->makingMove = true;

    for (Piece* piece : player->pieces) {
        std::vector<Move> moves = piece->getMoves(player);
        
        if (moves.size() > 0) {
            player->makingMove = false;
            return;
        }
    }

    player->makingMove = false;
    player->inCheckmate = true;
}

void doMove(Player* player, Move move) {
    player->matrix[move.piece->pos] = nullptr;
    move.piece->pos = move.nextPos;
    player->matrix[move.nextPos] = move.piece;

    if (move.eliminate) {
        for (int i = 0; i < player->opponent->pieces.size(); i++) {
            if (player->opponent->pieces[i] == move.eliminate) {
                player->opponent->pieces.erase(player->opponent->pieces.begin() + i);
            }
        }

        player->opponent->matrix[move.eliminate->pos] = nullptr;
    }
}

void undoMove(Player* player, Move move) {
    move.piece->pos = move.startPos;
    player->matrix[move.piece->pos] = move.piece;
    player->matrix[move.nextPos] = nullptr;

    if (move.eliminate) {
        player->opponent->pieces.push_back(move.eliminate);
        player->opponent->matrix[move.eliminate->pos] = move.eliminate;
    } 
}

bool isValidMoveInCheck(Player* player, Move move) {
    move.make(player);

    for (Piece* piece : player->opponent->pieces) {
        std::vector<Move> moves = piece->getMoves(player->opponent);
        for (Move& enemyMove : moves) {
            if (enemyMove.eliminate) {
                if (enemyMove.eliminate->isKing) {
                    move.undo(player);

                    return false;
                }
            }
        }
    }

    move.undo(player);
    
    return true;
}

bool checkEnemy(Player* opponent, Position pos) {       // useless function
    if (opponent->matrix[pos] != nullptr) {
        return true;
    }
    return false;
}

std::vector<Move> Piece::getMoves(Player* player) {
    cout << "ERROR - Piece::getMoves was called" << endl;
    
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

        Move move(pos, p, this);
        
        
        move.enPassantable = step - 1;
            
        moves.push_back(move);
    }
    
    Position upLeftPos(pos.col - 1, pos.row + 1 * player->color);
    if (upLeftPos.inBounds() && checkEnemy(player->opponent, upLeftPos)) {
        moves.push_back(Move(pos, upLeftPos, this, player->opponent->matrix[upLeftPos]));
    }

    Position upRightPos(pos.col + 1, pos.row + 1 * player->color);
    if (upRightPos.inBounds() && checkEnemy(player->opponent, upRightPos)) {
        moves.push_back(Move(pos, upRightPos, this, player->opponent->matrix[upRightPos]));
    }

    if (player->opponent->enPassant) {
        Piece* thePawn = player->opponent->enPassant;
        if (pos == Position(thePawn->pos.col + 1, thePawn->pos.row) || pos == Position(thePawn->pos.col - 1, thePawn->pos.row)) {
            moves.push_back(Move(pos, Position(thePawn->pos.col, thePawn->pos.row + player->color), this, thePawn));
        }
    }

    if (player->makingMove) {
        player->makingMove = false;

        std::vector<Move> actualMoves;
        
        for (Move& move : moves) {
            if (isValidMoveInCheck(player, move)) {
                actualMoves.push_back(move);
            }
        }

        player->makingMove = true;

        return actualMoves;
    }

    return moves;
}

std::vector<Move> Knight::getMoves(Player* player) {
    vector<Move> moves;

    // check for collision/out of bounds etc
    moves.push_back(Move(pos, Position(pos.col + 1, pos.row + 2), this));
    moves.push_back(Move(pos, Position(pos.col - 1, pos.row + 2), this));
    moves.push_back(Move(pos, Position(pos.col + 1, pos.row - 2), this));
    moves.push_back(Move(pos, Position(pos.col - 1, pos.row - 2), this));
    moves.push_back(Move(pos, Position(pos.col + 2, pos.row + 1), this));
    moves.push_back(Move(pos, Position(pos.col + 2, pos.row - 1), this));
    moves.push_back(Move(pos, Position(pos.col - 2, pos.row + 1), this));
    moves.push_back(Move(pos, Position(pos.col - 2, pos.row - 1), this));

    //experimental
    vector<Move> checkedMoves;

    for (Move move : moves) {
        if (move.nextPos.inBounds() && !player->matrix[move.nextPos]) {
            if (checkEnemy(player->opponent, move.nextPos)) {
                checkedMoves.push_back(Move(pos, move.nextPos, this, player->opponent->matrix[move.nextPos]));
            } else {
                checkedMoves.push_back(Move(pos, move.nextPos, this));
            }
        }
    }

    if (player->makingMove) {
        player->makingMove = false;
        
        std::vector<Move> actualMoves;
    
        for (Move& move : checkedMoves) {
            if (isValidMoveInCheck(player, move)) {
                actualMoves.push_back(move);
            }
        }

        player->makingMove = true;

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
            moves.push_back(Move(pos, p, this, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(pos, p, this));
    }

    // up right
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col + step, pos.row + step);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(pos, p, this, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(pos, p, this));
    }

    // down left
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col - step, pos.row - step);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(pos, p, this, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(pos, p, this));
    }

    // down right
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col + step, pos.row - step);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(pos, p, this, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(pos, p, this));
    }

    if (player->makingMove) {
        player->makingMove = false;
        
        std::vector<Move> actualMoves;
    
        for (Move& move : moves) {
            if (isValidMoveInCheck(player, move)) {
                actualMoves.push_back(move);
            }
        }

        player->makingMove = true;

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
            moves.push_back(Move(pos, p, this, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(pos, p, this));
    }

    // down
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col, pos.row - step);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(pos, p, this, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(pos, p, this));
    }

    // left
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col - step, pos.row);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(pos, p, this, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(pos, p, this));
    }

    // right
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col + step, pos.row);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(pos, p, this, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(pos, p, this));
    }

    if (player->makingMove) {
        player->makingMove = false;
        
        std::vector<Move> actualMoves;
    
        for (Move& move : moves) {
            if (isValidMoveInCheck(player, move)) {
                actualMoves.push_back(move);
            }
        }

        player->makingMove = true;

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
            moves.push_back(Move(pos, p, this, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(pos, p, this));
    }

    // up right
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col + step, pos.row + step);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(pos, p, this, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(pos, p, this));
    }

    // down left
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col - step, pos.row - step);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(pos, p, this, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(pos, p, this));
    }

    // down right
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col + step, pos.row - step);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(pos, p, this, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(pos, p, this));
    }

    // up
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col, pos.row + step);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(pos, p, this, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(pos, p, this));
    }

    // down
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col, pos.row - step);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(pos, p, this, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(pos, p, this));
    }

    // left
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col - step, pos.row);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(pos, p, this, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(pos, p, this));
    }

    // right
    for (int step = 1; step <= 8; step++) {
        Position p = Position(pos.col + step, pos.row);
        if (!p.inBounds() || player->matrix[p]) {
            break;
        }
        if (checkEnemy(player->opponent, p)) {
            moves.push_back(Move(pos, p, this, player->opponent->matrix[p]));
            break;
        }
        moves.push_back(Move(pos, p, this));
    }

    if (player->makingMove) {
        player->makingMove = false;
        
        std::vector<Move> actualMoves;
    
        for (Move& move : moves) {
            if (isValidMoveInCheck(player, move)) {
                actualMoves.push_back(move);
            }
        }

        player->makingMove = true;

        return actualMoves;
    }

    return moves;
}

std::vector<Move> King::getMoves(Player* player) {
    vector<Move> moves;

    moves.push_back(Move(pos, Position(pos.col + 1, pos.row + 1), this));
    moves.push_back(Move(pos, Position(pos.col + 1, pos.row - 1), this));
    moves.push_back(Move(pos, Position(pos.col - 1, pos.row + 1), this));
    moves.push_back(Move(pos, Position(pos.col - 1, pos.row - 1), this));

    moves.push_back(Move(pos, Position(pos.col + 1, pos.row), this));
    moves.push_back(Move(pos, Position(pos.col - 1, pos.row), this));
    moves.push_back(Move(pos, Position(pos.col, pos.row + 1), this));
    moves.push_back(Move(pos, Position(pos.col, pos.row - 1), this));

    //experimental
    vector<Move> checkedMoves;

    for (Move move : moves) {
        if (move.nextPos.inBounds() && !player->matrix[move.nextPos]) {
            if (checkEnemy(player->opponent, move.nextPos)) {
                checkedMoves.push_back(Move(pos, move.nextPos, this, player->opponent->matrix[move.nextPos]));
            } else {
                checkedMoves.push_back(Move(pos, move.nextPos, this));
            }
        }
    }

    if (!moved) {
        for (Piece* piece : player->pieces) {   // if rook hasnt moved, empty squares, king hasnt moved, any of the tiles arent attacked
            if (piece->isRook) {
                if (!piece->moved) {
                    bool spaceIsValid = true;
                    for (char ch = piece->pos.col + sign(pos.col - piece->pos.col); ch != pos.col; ch += sign(pos.col - piece->pos.col)) {
                        Position space(ch, pos.row);
                        if (piece->pos.col != ch && (player->matrix[space] || player->opponent->matrix[space] || space.isAttacked(player->opponent))) {
                            spaceIsValid = false;
                            break;
                        }
                    }

                    if (spaceIsValid) {
                        Position kingNextPos(pos.col + 2 * sign(piece->pos.col - pos.col), pos.row);
                        Position rookNextPos(pos.col + sign(piece->pos.col - pos.col), pos.row);
                        checkedMoves.push_back(Move(pos, kingNextPos, this, piece->pos, rookNextPos, piece));
                    }
                }
            }
        }
    }
    if (player->makingMove) {
        player->makingMove = false;
        
        std::vector<Move> actualMoves;
    
        for (Move& move : checkedMoves) {
            if (isValidMoveInCheck(player, move)) {
                actualMoves.push_back(move);
            }
        }

        player->makingMove = true;

        return actualMoves;
    }

    return checkedMoves;
}


