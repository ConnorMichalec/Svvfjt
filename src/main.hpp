#include <stdio.h>
#include <iostream>
#include "renderer.hpp"

class Main {
    public:
        Main();
        ~Main();
        void initialize();
        SDL_Renderer* getRenderer();
    
    private:
        SDL_Window *window;
        SDL_Renderer *sdl_renderer;
        int currentFPS = 0;
        void handleEvents();
        void cleanup();
        bool windowRunning;

        Renderer renderer;
};