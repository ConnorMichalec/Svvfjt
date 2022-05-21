#pragma once

#include "displayElements.hpp"


class Renderer {

    public: 
        Renderer();
        void Render(float primaryModifier);								// The primaryModifier value is what controls the dynamic synchronization to the audio, this will just be the current sample/frame's amplitude value.
        void Initialize(SDL_Renderer *sdl_renderer, SDL_Window *sdl_window, Audio *audio);

    private:
        SDL_Renderer *sdl_renderer;
        SDL_Window *sdl_window;
        DisplayElements *displayElements;
        int width;
        int height;

};
