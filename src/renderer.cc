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

Renderer::Renderer(SDL_Renderer *sdl_renderer, SDL_Window *sdl_window, Process process) {
    this->sdl_renderer = sdl_renderer;
    this->sdl_window = sdl_window;

    this->displayElements = new DisplayElements(sdl_renderer, sdl_window);

    SDL_GetWindowSize(sdl_window, &width, &height);


    srand(time(NULL));
}

void Renderer::Render() {

    SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);

    SDL_RenderClear(sdl_renderer);

    displayElements->simpleSineLine(500, 5);


    SDL_RenderPresent(sdl_renderer);
}

