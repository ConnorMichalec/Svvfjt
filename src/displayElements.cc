/*  Defines geometry and effects to render */

#include "displayElements.hpp"

DisplayElements::DisplayElements(SDL_Renderer *sdl_renderer, SDL_Window *sdl_window) {
    this->sdl_window = sdl_window;
    this->sdl_renderer = sdl_renderer;

    SDL_GetWindowSize(sdl_window, &width, &height);





}

DisplayElements::~DisplayElements() {

}

void DisplayElements::simpleSineLine(int y, int modifier) {
    const int lineResolution = 500;
    

    int segLength = (int)width/(lineResolution);
    for(int index = 0; index<lineResolution; index++) {
        SDL_SetRenderDrawColor(sdl_renderer, 255, 0, 0, 255);

        SDL_RenderDrawLine(sdl_renderer, segLength*index, y+(sin(index/5)*SDL_GetTicks()*0.1), segLength*(index+1), y+(sin((index+1)/5)*SDL_GetTicks()*0.1));
    }
}
