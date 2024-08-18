#include "chess.h"
#include "piecetypes.h"
#include "textures.h"

#include <iostream>

using namespace std; // remove later

void Chess::switchTurns() {     // fix this
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
        return Position('A' + 7 - (x / 100), y / 100 + 1);
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
            Move* validMove = nullptr;

            for (Move move : moves) {
                if (move.pos.col == clickedPos.col && move.pos.row == clickedPos.row) { // add operator for this
                    validMove = &move;
                    break;
                }
            }
            
            if (validMove) {
                play->selecting->pos = clickedPos;      // make move, change pos, change moved bool
                play->selecting->moved = true;
                if (validMove->eliminate) {
                    cout << "white piece count: " << white.pieces.size() << endl;
                    for (int i = 0; i < play->opponent->pieces.size(); i++) {
                        if (play->opponent->pieces[i] == validMove->eliminate) {
                            play->opponent->pieces.erase(play->opponent->pieces.begin() + i);
                            break;
                        }
                    }
                    cout << "white piece count: " << white.pieces.size() << endl;
                }
                cout << endl << white.pieces.size() << endl << endl;
                checkForCheck(play);
                cout << endl << white.pieces.size() << endl << endl;
                checkForCheck(play->opponent);
                cout << endl << white.pieces.size() << endl << endl;
            }
            
            white.matrix.reset();
            cout << endl << white.pieces.size() << endl << endl;
            for (Piece* piece : white.pieces) {
                white.matrix[piece->pos] = piece;
            }

            black.matrix.reset();

            for (Piece* piece : black.pieces) {
                black.matrix[piece->pos] = piece;
            }

            play->selecting = nullptr;  // unselect when clicked no piece
            if (validMove) {
                switchTurns();
            }
            moves = {};
        }
    } else {
        play->selecting = nullptr;      // when click same piece, unselect
        moves = {};
    }
}

void Chess::checkForCheck(Player* player) {
    player->opponent->inCheck = false;
    // NOTE: ERROR HERE!!
    for (Piece* piece : player->pieces) {
        std::vector<Move> moves = piece->getMoves(player);
        for (Move& move : moves) {
            if (move.eliminate) {
                if (move.eliminate->isKing) {
                    player->opponent->inCheck = true;
                    cout << "omg someones in check..." << endl;
                    return;
                }
            }
        }
    }
}






void Chess::mouseRelease(SDL_Event e) {
    // is this necessary!
}


void Chess::update() {
    
    // if (SDL_ == 0) {
    for (auto& row : white.matrix.matrix) {
        for (Piece* piece : row) {
            if (!piece) {
                cout << "o ";
            } else {
                cout << "x ";
            }
        }
        cout << endl;
    }

    cout << endl;
    // }
}