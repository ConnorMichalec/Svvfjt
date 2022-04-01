#include "renderer.hpp"
#include "audioSynthesis.hpp"
#include "userin.hpp"

class Process {
    public:
        Process();
        ~Process();
		void Initialize(Renderer *renderer, Audio *audio, UserInput *userin);
		void Tick();
	
	private:
		Audio *audio;
		UserInput *userinput;
		Renderer *renderer;
};