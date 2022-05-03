#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class DisplayElements {
    public:
        DisplayElements(SDL_Renderer *sdl_renderer, int canvasWidth, int canvasHeight);
        ~DisplayElements();

        void SimpleSineLine(int y, int modifier);


    private:
        SDL_Renderer *sdl_renderer;
        int width;
        int height;
};