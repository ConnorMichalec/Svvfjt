#include "audioSynthesis.hpp"



// Refer to: https://ccrma.stanford.edu/software/stk/crealtime.html

// All these are deafult global values
float frequency = 440.0;
int waveform = 0;
float modulator = 0;


int streamTick(void *outputBuffer, void *inputBuffer,
                                unsigned int nBufferFrames,
                                double streamTime,
                                RtAudioStreamStatus status,
                                void *userData ) {

    StkFloat *samples = (StkFloat *) outputBuffer;              // This holds the frames to send to the audio driver, 


	Audio *audioObject = (Audio*) userData;

    for ( unsigned int i=0; i<nBufferFrames; i++ )
		*samples++ = audioObject->FetchNextAudioFrame();		// Custom operator tells to increment frame and set this frame to the desired amplitude.


	return 0;

}

Audio::Audio() {
    dac = new RtAudio;
	currentAudioFrame = new StkFloat();
	audioFrameIndex = new long();

	sineTone = new SineWave();
	sineTone->setFrequency(frequency);
	sawTone = new BlitSaw(frequency);
	squareTone = new BlitSquare(frequency);
}

void Audio::InitializeAudiostream() {

    Stk::setSampleRate(44100.0);
    Stk::showWarnings(true);

    
    RtAudio::StreamParameters parameters;						// Figure out how many bytes in an StkFloat and setup the RtAudio stream.
    
    parameters.deviceId = dac->getDefaultOutputDevice();
    parameters.nChannels = 1;									// Mono audio

    RtAudioFormat format = ( sizeof(StkFloat) == 8 ) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
    unsigned int bufferFrames = RT_BUFFER_SIZE;					// This is the size of the sample/frame buffer that will accumulate before sending to the audio driver

    try {
        dac->openStream( &parameters, NULL, format, (unsigned int) Stk::sampleRate(), &bufferFrames, &streamTick, (void *) this );
    }
        catch ( RtAudioError &error ) {
        error.printMessage();
    }

    dac->startStream();											// Start sending buffer to driver

}

/**
 * Progress to the next audio frame, calculate and return the amplitude
 * @return The next frame's amplitude
 */
StkFloat Audio::FetchNextAudioFrame() {
	switch(waveform) {
		case(0):
			*currentAudioFrame = sineTone->tick();
			break;

		case(1):
			*currentAudioFrame = sawTone->tick();
			break;

		case(2):
			*currentAudioFrame = squareTone->tick();
			break;

		default:
			*currentAudioFrame = sineTone->tick();
			break;

	}


	*audioFrameIndex = *audioFrameIndex+1;						// Unsure why ++ doesn't work

	return(*currentAudioFrame);
}

/**
 * Return the last audio frame/sample sent to buffer, use this for visuals to get what is currently being played
 * @return The current frame's amplitude
 */
StkFloat Audio::GetCurrentAudioFrame() {
	return(*currentAudioFrame);
}

/**
 * @return the current total amount of frames ever sent to driver
 */
long* Audio::GetCurrentAudioFrameIndex() {
	return(audioFrameIndex);	
}

/**
 * @return the current waveform being used by the audio engine
 */
int Audio::GetCurrentWaveform() {
	return(waveform);
}

/**
 * Receives information about what parameters to update 
 */
void Audio::ReceiveControlParameters(int waveform, float frequency, float modulator) {
	// scope resolution operator

	if(waveform!=::waveform) {
		::waveform = waveform;
	}

	if(frequency!=::frequency) {
		::frequency = frequency;
		
	}

	if(modulator!=::modulator) {
		::modulator = modulator;
	}
}



Audio::~Audio() {
    dac->closeStream();
    delete dac;
	delete currentAudioFrame;
}


