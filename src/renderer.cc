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

Renderer::Renderer(SDL_Renderer *sdl_renderer, int width, int height) {
    this->height = height;
    this->width = width;
    this->sdl_renderer = sdl_renderer;

    srand(time(NULL));
}

void Renderer::Render() {

    SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);

    SDL_RenderClear(sdl_renderer);


    const int lineResolution = 500;
    

    int segLength = (int)width/(lineResolution);
    for(int index; index<lineResolution; index++) {
        SDL_SetRenderDrawColor(sdl_renderer, 255, 0, 0, 255);

        SDL_RenderDrawLine(sdl_renderer, segLength*index, (height/2)+(sin(index/5)*SDL_GetTicks()*0.1), segLength*(index+1), (height/2)+(sin((index+1)/5)*SDL_GetTicks()*0.1));

        SDL_SetRenderDrawColor(sdl_renderer, 0, 255, 0, 255);
        SDL_RenderDrawLine(sdl_renderer, segLength*index, (height/2)-(sin(index/5)*SDL_GetTicks()*0.2), segLength*(index+1), (height/2)-(sin((index+6)/5)*SDL_GetTicks()*0.2));
    }

    SDL_RenderPresent(sdl_renderer);
}

