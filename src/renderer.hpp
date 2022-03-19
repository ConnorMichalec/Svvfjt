#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Renderer {

    public: 
        Renderer();
        void Render(SDL_Renderer *sdl_renderer);

};