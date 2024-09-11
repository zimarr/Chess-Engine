#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>

#include "text.h"

class Panel {
    public:
        Panel() {}
        Panel(int w, int h);
        
        void draw(SDL_Renderer* rend);

        void addText(int x, int y, SDL_Renderer* rend, const char *str);
        
        void initTexts(SDL_Renderer* rend);

    private:    
        TTF_Font* font;
        SDL_Texture* font_texture;

        std::vector<Text*> texts;

        int width;
        int height;

};