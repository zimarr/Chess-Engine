#include "player.h"

Player* Player::getCopy() {
    Player* copy = new Player(*this);

    copy->opponent = new Player(*opponent);

    copy->opponent->opponent = copy;

    copy->selecting = copy->opponent->selecting = nullptr;

    for (int i = 0; i < pieces.size(); i++) {
        copy->pieces[i] = pieces[i]->clone();

        if (opponent->enPassant == pieces[i]) {
            copy->opponent->enPassant = copy->pieces[i];
        }

        if (opponent->tempEnPassant == pieces[i]) {
            copy->opponent->tempEnPassant = copy->pieces[i];
        }
    }

    for (int i = 0; i < opponent->pieces.size(); i++) {
        copy->opponent->pieces[i] = opponent->pieces[i]->clone();

        if (enPassant == opponent->pieces[i]) {
            copy->enPassant == copy->opponent->pieces[i];
        }

        if (tempEnPassant == opponent->pieces[i]) {
            copy->tempEnPassant == copy->opponent->pieces[i];
        }
    }

    return copy;
}