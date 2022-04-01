#include "process.hpp"

class Main {
    public:
        Main();
        ~Main();
        void Initialize();
        void RunMain();
        SDL_Renderer* GetRenderer();
    
    private:
        SDL_Window *window;
        SDL_Renderer *sdl_renderer;

        int currentFPS = 0;
        void handleEvents();
        void cleanup();
        bool windowRunning;

        Renderer *renderer;
        Process *process;
        Audio *audio;
        UserInput *userinput;
};