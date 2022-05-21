#include "renderer.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <random>
#include <time.h>
#include <math.h>

#define PI 3.141592

int randrange(int min, int max) {
    return((int) (rand()%max-min)+min);
}

Renderer::Renderer() {

}

void Renderer::Initialize(SDL_Renderer *sdl_renderer, SDL_Window *sdl_window, Audio* audio) {
    this->sdl_renderer = sdl_renderer;
    this->sdl_window = sdl_window;

    SDL_GetWindowSize(sdl_window, &width, &height);

    this->displayElements = new DisplayElements(sdl_renderer, width, height, audio);


    srand(time(NULL));
}

void Renderer::Render(float primaryModifier) {

    SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);

    SDL_RenderClear(sdl_renderer);

    displayElements->SimpleSineLine(500, 5);

    SDL_RenderPresent(sdl_renderer);
}

