#include <SDL.h>
#include "chessscreen.h"

int main(int argc, char *argv[]) {    
    ChessScreen chessScreen;
    chessScreen.init("Chess", SDL_WINDOWPOS_CENTERED,  SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_BORDERLESS);
    chessScreen.loop();
    return 0;
}