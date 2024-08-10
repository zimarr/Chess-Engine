#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "piecetypes.h"
#include "player.h"
#include "classifier.h"

Pawn::Pawn(char  c, int r, Color clr) {
    pos = Position(c, r);
    
    color = clr;

    texture = IMG_LoadTexture(Piece::rend, "./res/pawn.png");

    if (!(texture)) {
        std::cout << "ERROR" << std::endl;
    }   
}

Knight::Knight(char  c, int r, Color clr) {
    pos = Position(c, r);

    color = clr;
    
    texture = IMG_LoadTexture(Piece::rend, "./res/knight.png");

    if (!(texture)) {
        std::cout << "ERROR" << std::endl;
    }   
}

Bishop::Bishop(char  c, int r, Color clr) {
    pos = Position(c, r);

    color = clr;
    
    texture = IMG_LoadTexture(Piece::rend, "./res/bishop.png");

    if (!(texture)) {
        std::cout << "ERROR" << std::endl;
    }   
}

Rook::Rook(char  c, int r, Color clr) {
    pos = Position(c, r);

    color = clr;
    
    texture = IMG_LoadTexture(Piece::rend, "./res/rook.png");

    if (!(texture)) {
        std::cout << "ERROR" << std::endl;
    }   
}

Queen::Queen(char  c, int r, Color clr) {
    pos = Position(c, r);

    color = clr;
    
    texture = IMG_LoadTexture(Piece::rend, "./res/queen.png");

    if (!(texture)) {
        std::cout << "ERROR" << std::endl;
    }   
}

King::King(char  c, int r, Color clr) {
    pos = Position(c, r);

    color = clr;
    
    texture = IMG_LoadTexture(Piece::rend, "./res/king.png");

    if (!(texture)) {
        std::cout << "ERROR" << std::endl;
    }   
}







// SDL_Texture* Pawn::texture = IMG_LoadTexture(rend, "./res/pawn.png");