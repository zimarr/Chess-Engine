#include <SDL.h>
#include <SDL_image.h>
#include "chess.h"
#include "piece.h"
#include "piecetypes.h"
#include "drawpieces.h"

Chess::Chess() {
    white = Player(Color::WHITE);
    black = Player(Color::BLACK);
    white.opponent = &black;
    black.opponent = &white;
    play = &white;

    flipEnabled = false;
}

#include <iostream>
using namespace std;

void Chess::initPieces(SDL_Renderer *rend) {
    Piece::rend = rend;

    //white pawns
    for (char col = 'A'; col <= 'H'; col++) {
        white.pieces.push_back(new Pawn(col, 2, WHITE));
    }

    //white knights
    white.pieces.push_back(new Knight('C', 1, WHITE));
    white.pieces.push_back(new Knight('F', 1, WHITE));

    //white bishops
    white.pieces.push_back(new Bishop('B', 1, WHITE));
    white.pieces.push_back(new Bishop('G', 1, WHITE));

    //white rooks    
    white.pieces.push_back(new Rook('A', 1, WHITE));
    white.pieces.push_back(new Rook('H', 1, WHITE));

    //white queen
    white.pieces.push_back(new Queen('D', 1, WHITE));

    //white king
    white.pieces.push_back(new King('E', 1, WHITE));

    //black pawns
    for (char col = 'A'; col <= 'H'; col++) {
        black.pieces.push_back(new Pawn(col, 7, BLACK));
    }

    //black knights
    black.pieces.push_back(new Knight('C', 8, BLACK));
    black.pieces.push_back(new Knight('F', 8, BLACK));

    //black bishops
    black.pieces.push_back(new Bishop('B', 8, BLACK));
    black.pieces.push_back(new Bishop('G', 8, BLACK));

    //black rooks    
    black.pieces.push_back(new Rook('A', 8, BLACK));
    black.pieces.push_back(new Rook('H', 8, BLACK));

    //black queen
    black.pieces.push_back(new Queen('D', 8, BLACK));

    //black king
    black.pieces.push_back(new King('E', 8, BLACK));

    for (Piece* piece : white.pieces) {
        white.matrix[piece->pos] = piece;
    }

    for (Piece* piece : black.pieces) {
        black.matrix[piece->pos] = piece;
    }
}

// void Chess::update() {
//     // call all logic stuffs
// }

void Chess::draw(SDL_Renderer *rend) {
    SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
    
    for (Piece* piece : white.pieces) {
        piece->draw(play->color, flipEnabled);
    }

    for (Piece* piece : black.pieces) {
        piece->draw(play->color, flipEnabled);
    }

    drawMoves();
}