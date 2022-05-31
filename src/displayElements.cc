/*  Defines geometry and effects to render */

#include "displayElements.hpp"
#include <math.h>

DisplayElements::DisplayElements(SDL_Renderer *sdl_renderer, int canvasWidth, int canvasHeight, Audio* audio) {
    this->sdl_renderer = sdl_renderer;

    this->audio = audio;

    this->width = canvasWidth;
    this->height = canvasHeight;
}

DisplayElements::~DisplayElements() {

}

void DisplayElements::SimpleSineLine(int y) {
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

	float freq = audio->GetFrequency();
	long frame = *audio->GetCurrentAudioFrameIndex();
	int mod = audio->GetModAmp();
	if(mod<1)
		mod=1;

        SDL_RenderDrawLine(sdl_renderer, segLength*index, y + sin(pow(index*0.0003*freq,1.3) + frame/1000)*80*pow(mod,0.5), segLength*(index+1), y + sin(pow((index+1)*0.0003*freq,1.3) + frame/1000)*80*pow(mod,0.5) );

    }
}

void DisplayElements::Rect(int x, int y) {

	int wave = audio->GetCurrentWaveform();

	switch(wave) {
		case(0):
        		SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 255, 255);
			break;
		case(1):
        		SDL_SetRenderDrawColor(sdl_renderer, 0, 255, 255, 255);
			break;
		case(2):
        		SDL_SetRenderDrawColor(sdl_renderer, 0, 255, 0, 255);
			break;
		default:
			break;
	}
	SDL_Rect r;
	r.x = x;
	r.y = y;
	r.w = 500;
	r.h = 500;

	bool rythmActive = audio->GetRythmWaiting();
	if(!rythmActive)
		SDL_RenderDrawRect(sdl_renderer, &r);
}
