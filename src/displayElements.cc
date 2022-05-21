/*  Defines geometry and effects to render */

#include "displayElements.hpp"

DisplayElements::DisplayElements(SDL_Renderer *sdl_renderer, int canvasWidth, int canvasHeight, Audio* audio) {
    this->sdl_renderer = sdl_renderer;

    this->audio = audio;

    this->width = canvasWidth;
    this->height = canvasHeight;
}

DisplayElements::~DisplayElements() {

}

void DisplayElements::SimpleSineLine(int y, int modifier) {
    const int lineResolution = 500;
    

    int segLength = (int)width/(lineResolution);
    for(int index = 0; index<lineResolution; index++) {
	int wave = audio->GetCurrentWaveform();

	switch(wave) {
		case(0):
        		SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 0, 255);
			break;
		case(1):
        		SDL_SetRenderDrawColor(sdl_renderer, 255, 0, 255, 255);
			break;
		case(2):
        		SDL_SetRenderDrawColor(sdl_renderer, 255, 0, 0, 255);
			break;
		default:
			break;
	}

			

        SDL_RenderDrawLine(sdl_renderer, segLength*index, y + (index), segLength*(index+1), y+(tan((index+1)/5)*SDL_GetTicks()*0.1));
    }
}
