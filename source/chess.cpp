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
        white.pieces.push_back(new Pawn(col, 2));
    }

    //white knights
    white.pieces.push_back(new Knight('C', 1));
    white.pieces.push_back(new Knight('F', 1));

    //white bishops
    white.pieces.push_back(new Bishop('B', 1));
    white.pieces.push_back(new Bishop('G', 1));

    //white rooks    
    white.pieces.push_back(new Rook('A', 1));
    white.pieces.push_back(new Rook('H', 1));

    //white queen
    white.pieces.push_back(new Queen('D', 1));

    //white king
    white.pieces.push_back(new King('E', 1));

    //black pawns
    for (char col = 'A'; col <= 'H'; col++) {
        black.pieces.push_back(new Pawn(col, 7));
    }

    //black knights
    black.pieces.push_back(new Knight('C', 8));
    black.pieces.push_back(new Knight('F', 8));

    //black bishops
    black.pieces.push_back(new Bishop('B', 8));
    black.pieces.push_back(new Bishop('G', 8));

    //black rooks    
    black.pieces.push_back(new Rook('A', 8));
    black.pieces.push_back(new Rook('H', 8));

    //black queen
    black.pieces.push_back(new Queen('D', 8));

    //black king
    black.pieces.push_back(new King('E', 8));

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