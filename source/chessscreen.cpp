#include <iostream>
#include "chessscreen.h"
#include "textures.h"

#include <SDL_image.h>

ChessScreen::ChessScreen() {
    width = 0;
    height = 0;
    running = false;
}

void ChessScreen::init(const char title[], int x, int y, int w, int h, int flags) {
    if(SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "ERROR" << std::endl; return;
    }

    window = SDL_CreateWindow("Thing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);

    if (!window) {
        std::cout << "ERROR" << std::endl; return;
    }

    rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!rend) {
        std::cout << "ERROR" << std::endl; return;
    }

    SDL_Surface *boardSurf = IMG_Load("./res/board.png");

    if (!boardSurf) {
        std::cout << "ERROR" << std::endl; return;
    }

    board = SDL_CreateTextureFromSurface(rend, boardSurf);

    if (!board) {
        std::cout << "ERROR" << std::endl; return;
    }

    SDL_FreeSurface(boardSurf);

    width = w;
    height = h;
    running = true;
    initTextures();
    chess.initPieces(rend);
}

void ChessScreen::initTextures() {
    Textures::move = IMG_LoadTexture(rend, "./res/move.png");
    
    if (!Textures::move) {
        std::cout << "die" << std::endl;
    }

    Textures::movetake = IMG_LoadTexture(rend, "./res/movetake.png");
}

void ChessScreen::loop() {
    const int DELAY = 1000 / 60;
    int frameStart;
    int frameTime;

    while(running) {        
        frameStart = SDL_GetTicks();

        handleEvents();
        chess.update();
        draw();        

        frameTime = SDL_GetTicks() - frameStart;

        if (DELAY > frameTime) {
            SDL_Delay(DELAY - frameTime);
        }
    }

    quit();
}

void ChessScreen::draw() {
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    SDL_RenderClear(rend);

    SDL_RenderCopy(rend, board, NULL, NULL);
    chess.draw(rend);

    SDL_RenderPresent(rend);
}

void ChessScreen::handleEvents() {
    SDL_Event e;
    SDL_PollEvent(&e);

    if (e.type == SDL_QUIT) {
        running = false;
    }

    if (e.type == SDL_MOUSEBUTTONDOWN) {
        chess.mouseClick(e);
    }

    if (e.type == SDL_MOUSEBUTTONUP) {
        chess.mouseRelease(e);
    }
}