#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class DisplayElements {
    public:
        DisplayElements(SDL_Renderer *sdl_renderer, SDL_Window *sdl_window);
        ~DisplayElements();

        void simpleSineLine(int y, int modifier);


    private:
        SDL_Renderer *sdl_renderer;
        SDL_Window *sdl_window;
        int width;
        int height;
};