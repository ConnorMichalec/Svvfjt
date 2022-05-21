#pragma once

#include "audioSynthesis.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class DisplayElements {
    public:
	Audio* audio;
        DisplayElements(SDL_Renderer *sdl_renderer, int canvasWidth, int canvasHeight, Audio* audio);
        ~DisplayElements();

        void SimpleSineLine(int y, int modifier);


    private:
        SDL_Renderer *sdl_renderer;
        int width;
        int height;
};
