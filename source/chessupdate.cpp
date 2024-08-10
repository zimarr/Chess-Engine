#include "chess.h"
#include "piecetypes.h"
#include "textures.h"

#include <iostream>

using namespace std; // remove later

void Chess::switchTurns() {
    (play == &white) ? play = &black : play = &white;
}

void Chess::drawMoves() {
    for (Move move : moves) {
        SDL_Rect rect{move.pos.getXPos(play->color, flipEnabled), move.pos.getYPos(play->color, flipEnabled), 100, 100};
        if (move.eliminate) {
            SDL_RenderCopy(Piece::rend, Textures::movetake, NULL, &rect);
        } else {    
            SDL_RenderCopy(Piece::rend, Textures::move, NULL, &rect);
        }
    }
}

Piece* Chess::getClickedPiece(int x, int y) {
    for (Piece* piece : play->pieces) {
        if (x > piece->pos.getXPos(play->color, flipEnabled) && x < piece->pos.getXPos(play->color, flipEnabled) + 100 && y > piece->pos.getYPos(play->color, flipEnabled) && y < piece->pos.getYPos(play->color, flipEnabled) + 100) {
            return piece;
        }
    }

    return nullptr;
}

Position Chess::getClickedPosition(int x, int y) {
    if (!flipEnabled | play->color == WHITE) {
        return Position(x / 100 + 'A', -1 * (y / 100 - 8));
    } else {
        return Position('H' - (x / 100), 1 + (8 - (y / 100)));
    }
}

void Chess::mouseClick(SDL_Event e) {
    Piece *clickedPiece = getClickedPiece(e.button.x, e.button.y);

    if (clickedPiece != play->selecting) {
        if (clickedPiece) {
            play->selecting = clickedPiece;
            moves = clickedPiece->getMoves(play);
            
            cout << "moves: ";    
            for (Move move : moves) {
                cout << move.pos.col << move.pos.row << ", ";
            }
            cout << endl;
        } else {
            Position clickedPos = getClickedPosition(e.button.x, e.button.y);
            bool containsPos = false;

            for (Move move : moves) {
                if (move.pos.col == clickedPos.col && move.pos.row == clickedPos.row) { // add operator for this
                    containsPos = true;
                    break;
                }
            }
            
            if (containsPos) {
                play->selecting->pos = clickedPos;
                play->selecting->moved = true;
            }
            
            white.matrix.reset();
        
            for (Piece* piece : white.pieces) {
                white.matrix[piece->pos] = piece;
            }

            black.matrix.reset();

            for (Piece* piece : black.pieces) {
                black.matrix[piece->pos] = piece;
            }

            play->selecting = nullptr;  // unselect when clicked no piece
            if (containsPos) {
                switchTurns();
            }
            moves = {};
        }
    } else {
        play->selecting = nullptr;      // when click same piece, unselect
        moves = {};
    }
}

void Chess::mouseRelease(SDL_Event e) {
    // is this necessary!
}


void Chess::update() {
    
    



}