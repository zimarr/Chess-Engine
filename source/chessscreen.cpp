#include <iostream>
#include "chessscreen.h"
#include "textures.h"

#include <SDL_image.h>
#include <SDL_ttf.h>

ChessScreen::ChessScreen() {
    width = 0;
    height = 0;
    running = false;
}

void ChessScreen::init(const char title[], int x, int y, int w, int h, int flags) {
    if(SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "ERROR" << std::endl; return;
    }

    if (TTF_Init()) {
        std::cout << "TTF_Init failed! TTF_Error: " << TTF_GetError() << std::endl;
    }

    window = SDL_CreateWindow("Thing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN | flags);

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

    panel = Panel(300, h);

    width = w;
    height = h;
    running = true;
    initTextures();
    chess.initPieces(rend);
    panel.initTexts(rend);
    SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);
}

void ChessScreen::initTextures() {
    Textures::move = IMG_LoadTexture(rend, "./res/move.png");
    
    if (!Textures::move) {
        std::cout << "ERROR" << std::endl;
    }

    Textures::movetake = IMG_LoadTexture(rend, "./res/movetake.png");

    if (!Textures::movetake) {
        std::cout << "ERROR" << std::endl;
    }

    settingsbuttonclosed = IMG_LoadTexture(rend, "./res/settingsbuttonclosed.png");

    if (!settingsbuttonclosed) {
        std::cout << "ERROR" << std::endl;
    }

    settingsbuttonopen = IMG_LoadTexture(rend, "./res/settingsbuttonopen.png");

    if (!settingsbuttonopen) {
        std::cout << "ERROR" << std::endl;
    }
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

    SDL_Rect destRect{0, 0, 800, 800};
    SDL_RenderCopy(rend, board, NULL, &destRect);

    chess.draw(rend, 0, panel.isShowMovesEnabled());

    SDL_Rect settingsrect{panel.getWidth(), 0, 50, 50};
    
    if (panel.isOpen()) {
        SDL_RenderCopy(rend, settingsbuttonopen, NULL, &settingsrect);
    } else {
        SDL_RenderCopy(rend, settingsbuttonclosed, NULL, &settingsrect);
    }
    
    panel.draw(rend);

    SDL_RenderPresent(rend);
}

void ChessScreen::handleEvents() {
    SDL_Event e;
    SDL_PollEvent(&e);

    if (e.type == SDL_QUIT) {
        running = false;
    }

    if (e.type == SDL_MOUSEBUTTONDOWN) {
        if (e.button.x < 50 + panel.getWidth() && e.button.x > panel.getWidth() && e.button.y < 50) {
            panel.setOpen();
        } else if (!panel.isOpen()) {
            chess.mouseClick(e);
        }

        if (panel.isOpen()) {
            panel.checkAllBoxes(e.button.x, e.button.y);
        }

        chess.flipEnabled = panel.isFlipEnabled();
    }

    if (e.type == SDL_MOUSEBUTTONUP) {
        chess.mouseRelease(e);
    }
}