#include "renderer.hpp"

Renderer::Renderer() {

}

void Renderer::Render(SDL_Renderer *sdl_renderer) {
    SDL_SetRenderDrawColor(sdl_renderer, 255, 0, 0, 255);

    SDL_RenderClear(sdl_renderer);

    SDL_RenderPresent(sdl_renderer);
}