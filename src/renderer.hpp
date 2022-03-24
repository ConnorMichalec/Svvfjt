#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class Renderer {

    public: 
        Renderer(SDL_Renderer *sdl_renderer, int width, int height);
        void Render();

    private:
        SDL_Renderer *sdl_renderer;
        int width;
        int height;

};