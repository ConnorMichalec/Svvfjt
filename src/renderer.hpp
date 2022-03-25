#include "process.hpp"
#include "displayElements.hpp"


class Renderer {

    public: 
        Renderer(SDL_Renderer *sdl_renderer, SDL_Window *sdl_window, Process process);
        void Render();

    private:
        SDL_Renderer *sdl_renderer;
        SDL_Window *sdl_window;
        DisplayElements *displayElements;
        int width;
        int height;

};