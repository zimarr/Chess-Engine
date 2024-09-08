#include <iostream>
#include "move.h"
#include "player.h"

int sign(int a);

using namespace std;

void Move::make(Player* player) {
    player->matrix[piece->pos] = nullptr;
    piece->pos = nextPos;
    player->matrix[nextPos] = piece;

    if (castle) {
        player->matrix[castle->pos] = nullptr;
        castle->pos = castleNextPos;
        player->matrix[castleNextPos] = castle;
    }

    if (enPassantable) {
        player->tempEnPassant = player->enPassant;
        player->enPassant = piece;
    }

    if (eliminate) {
        for (int i = 0; i < player->opponent->pieces.size(); i++) {
            if (player->opponent->pieces[i] == eliminate) {
                player->opponent->pieces.erase(player->opponent->pieces.begin() + i);
            }
        }

        player->opponent->matrix[eliminate->pos] = nullptr;

        player->opponent->points -= eliminate->value;
    }
}

void Move::undo(Player* player) {
    piece->pos = startPos;
    player->matrix[piece->pos] = piece;
    player->matrix[nextPos] = nullptr;

    if (castle) {
        castle->pos = castleStartPos;
        player->matrix[castle->pos] = castle;
        player->matrix[castleNextPos] = nullptr;
    }

    if (enPassantable) {
        player->enPassant = player->tempEnPassant;
        player->tempEnPassant = nullptr;
    }

    if (eliminate) {
        player->opponent->pieces.push_back(eliminate);
        player->opponent->matrix[eliminate->pos] = eliminate;

        player->opponent->points += eliminate->value;
    } 
}