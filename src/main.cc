#include "main.hpp"

#include <stdio.h>
#include <iostream>


/**
 * TODO:
 * 
 * Improve efficiency by implementing more pass by reference on the currently passed by value functions.
 */

int main(int argc, const char * argv[]) {
    Main run = Main();

    run.RunMain();
}


Main::Main() {
    Initialize();

    userinput = new UserInput();
    audio = new Audio();
    process = new Process();//will i use this even?
    renderer = new Renderer();
}

/**
 * Free memory(happens after cleanup)
 */
Main::~Main() {
    delete userinput;
    delete audio;
    delete process;
    delete renderer;
}

void Main::Initialize() {
    windowRunning = true;

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow("", 0, 0, 1920, 1800, SDL_WINDOW_FULLSCREEN);	// This interacts directly with the framebuffer so no need for x-server.
	//window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, 0);
    }
} 

void Main::handleEvents() {
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    SDL_Event event;
    while( SDL_PollEvent( &event ) != 0 ) {

        switch(event.type) {
        case SDL_QUIT:
            windowRunning = false;
            break;
        default:
            break;
        }
    }
}

void Main::RunMain() {

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;  // calculated frame delay based on FPS
    Uint32 calculationStartTime;        // Calculation time marker, to calculate the final time to wait to get the fps to 60, as it will take some time to calculate appropraite things before frame render
    int calculationTime;                // time it takes to perform pre render calulations
    long countedFrames = 0;             // number of frames passed so far

    sdl_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(!sdl_renderer) {        // failed to initialize renderer 

        std::cout << "Renderer failed to initialize";
    }

    renderer->Initialize(sdl_renderer, window, audio);
	audio->InitializeAudiostream();
	process->Initialize(renderer, audio, userinput);

    while(windowRunning) {
        // how many ticks since initialization?
        calculationStartTime = SDL_GetTicks();

	userinput->Update();

        handleEvents();

        process->Tick();

	audio->ReceiveControlParameters((int) userinput->FetchP1(), userinput->FetchP2(), userinput->FetchP3());

   
        calculationTime = SDL_GetTicks() - calculationStartTime;                    // gets how long it took to process the main routine.
        if(calculationTime < frameDelay)                                            // If the calculations took less time then delay the amount of time to make it the target framerate, otherwise don't delay
        {
            SDL_Delay(frameDelay - calculationTime);                                // delay the amount of time it takes to make it 60fps minus the amount it took to perform calculations
        }

        currentFPS = countedFrames / (SDL_GetTicks() / 1000.0f);                    // calculated current FPS
        countedFrames++;

    }

    cleanup();
}

/**
 * Simply exit and cleanup the sdl window
 */
void Main::cleanup() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(sdl_renderer);
    SDL_Quit();
}

