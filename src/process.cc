/**
 * Handles the distribution for io among audio/visual (UNUSED - TODO DELETE)
 */

#include "process.hpp"

Process::Process() {

}

void Process::Initialize(Renderer *renderer, Audio *audio, UserInput *userin) {
	this->renderer = renderer;
	this->audio = audio;
	this->userinput = userin;
}

/**
 * Fetch any potential updates from GPIO then send this to the audio/visual
 */
void Process::Tick() {
	renderer->Render(audio->GetCurrentAudioFrame());
}

Process::~Process() {

}
