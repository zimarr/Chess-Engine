#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include "chess.h"
#include "panel.h"

class ChessScreen {
    public:
        ChessScreen();
        ~ChessScreen() {};

        void init(const char title[], int x, int y, int w, int h, int flags);
        void initTextures();

        void loop();
        void handleEvents();
        void quit() {};

        void draw();

        

    private:
        int height;
        int width;

        SDL_Window *window;
        

        SDL_Renderer *rend;

        SDL_Texture *board;

        Chess chess;

        bool running;

        Panel panel;
};