#include "chess.h"
#include "piecetypes.h"
#include "textures.h"

#include <iostream>

using namespace std; // remove later



void Chess::drawMoves() {
    for (Move move : moves) {
        // cout << Textures::move << endl;
        // Textures::move = IMG_LoadTexture(Piece::rend, "./res/move.png");
        SDL_Rect rect{(move.pos.col -  'A') * 100, (8 - move.pos.row) * 100, 100, 100};
        SDL_RenderCopy(Piece::rend, Textures::move, NULL, &rect);
    }
}

Piece* Chess::getClickedPiece(int x, int y) {
    for (Piece* piece : white.pieces) {
        if (x > piece->getXPos() && x < piece->getXPos() + 100 && y > piece->getYPos() && y < piece->getYPos() + 100) {
            return piece;
        }
    }

    return nullptr;
}

Position getClickedPosition(int x, int y) {
    return Position(x / 100 + 'A', -1 * (y / 100 - 8));
}

void Chess::mouseClick(SDL_Event e) {
    Piece *clickedPiece = getClickedPiece(e.button.x, e.button.y);

    if (clickedPiece != white.selecting) {
        if (clickedPiece) {
            white.selecting = clickedPiece;
            moves = clickedPiece->getMoves();
            
            // drawMoves();
            
            cout << "moves: ";    

            for (Move move : moves) {
                cout << move.pos.col << " " << move.pos.row << ", ";
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

            cout << "got here" << endl;
            
            if (containsPos) {
                cout << "got here2" << endl;
                cout << white.selecting->pos.col << endl;
                cout << clickedPos.col << endl;
                white.selecting->pos = clickedPos;
            }

            cout << "got here3" << endl;

            for (Piece* piece : white.pieces) {
                whiteMatrix[piece->pos] = piece;
            }

            white.selecting = nullptr;  // unselect when clicked no piece
            moves = {};
        }
    } else {
        white.selecting = nullptr;      // when click same piece, unselect
        moves = {};
    }


    

    /*
    

    if (selecting is false):

        get collision of what it is *only white for now
        
        get moves of that piece

        for each move, draw a tile indicating move

    else:

        unselect and undraw those moves
        
        set selecting to false

    
    */
}

void Chess::mouseRelease(SDL_Event e) {
    // is this necessary!
}


void Chess::update() {
    
    



}