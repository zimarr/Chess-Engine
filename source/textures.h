#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "piece.h"

// note: no texture error checking .. TODO ?

struct Textures {
    // have better rend management .. TODO
    static SDL_Texture* move;
    static SDL_Texture* movetake;
};

