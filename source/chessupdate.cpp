#include "chess.h"
#include "piecetypes.h"
#include "textures.h"

#include <iostream>

using namespace std; // remove later

void checkCheckmate(Player* player); // clean this up

void Chess::switchTurns() {     // fix this
    (play == &white) ? play = &black : play = &white;
}

void Chess::drawMoves() {
    for (Move move : moves) {
        SDL_Rect rect{move.nextPos.getXPos(play->color, flipEnabled), move.nextPos.getYPos(play->color, flipEnabled), 100, 100};
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

void simulate(Player* black, int step, std::vector<Move>& botMoves);

void Chess::mouseClick(SDL_Event e) {
    Piece *clickedPiece = getClickedPiece(e.button.x, e.button.y);

    if (clickedPiece != play->selecting) {
        if (clickedPiece) {
            play->makingMove = true;
            
            play->selecting = clickedPiece;
            moves = clickedPiece->getMoves(play);

            play->makingMove = false;
        } else {            
            Position clickedPos = getClickedPosition(e.button.x, e.button.y);
            Move* validMove = nullptr;

            for (Move move : moves) {
                if (move.nextPos == clickedPos) { // add operator for this
                    validMove = &move;
                    break;
                }
            }
            
            if (validMove) {
                validMove->make(play); // make move, change pos, change moved bool      
                
                play->selecting->moved = true;
                play->opponent->enPassant = nullptr;
                play->opponent->tempEnPassant = nullptr;
                
                if (validMove->eliminate) {
                    for (int i = 0; i < play->opponent->pieces.size(); i++) {
                        if (play->opponent->pieces[i] == validMove->eliminate) {
                            play->opponent->pieces.erase(play->opponent->pieces.begin() + i);
                            break;
                        }
                    }
                }

                checkForCheck(play);
                checkForCheck(play->opponent);
                
                checkCheckmate(play);
                checkCheckmate(play->opponent);
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
    
    for (Piece* piece : player->pieces) {
        std::vector<Move> moves = piece->getMoves(player);
        for (Move& move : moves) {
            if (move.eliminate) {
                if (move.eliminate->isKing) {
                    player->opponent->inCheck = true;
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
    
    if (white.inCheckmate) {
        cout << "BLACK WINS" << endl;
    }

    if (black.inCheckmate) {
        cout << "WHITE WINS" << endl;
    }

    // cout << white.pieces.size() << endl;

    // cout << "white: " << white.points << endl;
    // cout << "black: " << black.points << endl;

    // cout << "white enPassant: " << white.enPassant << endl;
    // cout << "temp white enPassant: " << white.tempEnPassant << endl;

    // cout << "black enPassant: " << black.enPassant << endl;
    // cout << "temp black enPassant: " << black.tempEnPassant << endl;

    // for (auto& row : white.matrix.matrix) {
    //     for (Piece* piece : row) {
    //         if (!piece) {
    //             cout << "o ";
    //         } else {
    //             cout << "x ";
    //         }
    //     }
    //     cout << endl;
    // }

    // cout << endl;

}