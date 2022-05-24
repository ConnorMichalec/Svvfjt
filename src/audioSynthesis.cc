#include "audioSynthesis.hpp"



// Refer to: https://ccrma.stanford.edu/software/stk/crealtime.html

// All these are deafult global values
float frequency;		// Frequency of waveform
int waveform;			// Waveform currently playing
float modulatorAmpOffset;
float modSpeed;
int rythmWaitDuration = 7000;	// How many cycles to wait before next beat
int rythmAliveDuration = 300;


int rythmWaitTime = 1;
int rythmAliveTime = 1;
bool rythmWaiting = false;

float currentMod = 0;
int currentModAmplitude = 0;

int samplesSinceLastChange = 0;			// Time since last input from user, (stop playing audio after certain time as not to annoy)
const int inactiveSamplesToIdle = 1000;		// After what amount of time without input from user should we go idle 

int streamTick(void *outputBuffer, void *inputBuffer,
                                unsigned int nBufferFrames,
                                double streamTime,
                                RtAudioStreamStatus status,
                                void *userData ) {

    StkFloat *samples = (StkFloat *) outputBuffer;              // This holds the frames to send to the audio driver, 



	Audio *audioObject = (Audio*) userData;

    for ( unsigned int i=0; i<nBufferFrames; i++ ) {
	*samples++ = audioObject->FetchNextAudioFrame();		// Custom operator tells to increment frame and set this frame to the desired amplitude.
	}



    return 0;

}

Audio::Audio() {
    dac = new RtAudio;
	currentAudioFrame = new StkFloat();
	audioFrameIndex = new long();

	sineTone = new SineWave();
	sawTone = new BlitSaw();
	squareTone = new BlitSquare();
	rythmTone =  new Noise();
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

	*audioFrameIndex = *audioFrameIndex+1;						// Unsure why ++ doesn't work

	updateModulator();

	if(samplesSinceLastChange < inactiveSamplesToIdle) {
		// Janky ass polyphony by adding all the samples together and hoping they act like waves should. Multiply by volume.
		*currentAudioFrame = toneTick()+rythmTick();
	}		
	else {
		// Don't play any audio
		*currentAudioFrame = 0;
	}


	return(*currentAudioFrame);
}

void Audio::updateModulator() {
	currentMod += modSpeed;

	currentModAmplitude = (int) (sin(currentMod)*modulatorAmpOffset);

	if(frequency + currentModAmplitude > 0) {
		sineTone->setFrequency(frequency + currentModAmplitude);
		sawTone->setFrequency(frequency + currentModAmplitude);
		squareTone->setFrequency(frequency + currentModAmplitude);
	}
}

StkFloat Audio::toneTick() {
	switch(waveform) {
		case(0):
			return(sineTone->tick());
			// no need to break since return

		case(1):
			return(sawTone->tick());

		case(2):
			return(squareTone->tick());

		default:
			return(sineTone->tick());
	}
}

StkFloat Audio::rythmTick() {
	if(rythmWaiting) {
		if(rythmWaitTime % rythmWaitDuration == 0) {
			rythmWaiting = false;			
			rythmWaitTime = 1;
		}
		else {
			rythmWaitTime++;
		}
	}
	else {
		if(rythmAliveTime % rythmAliveDuration == 0) {
			rythmWaiting = true;
			rythmAliveTime = 1;
		}
		else {
			rythmAliveTime++;
			return(rythmTone->tick());
		}
	}

	return 0;

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
void Audio::ReceiveControlParameters(int waveform, float frequency, float modulatorAmp, float modulatorSpeed, float rythmWaitDuration, float rythmAliveDuration) {
	samplesSinceLastChange++;
	
	// scope resolution operator
	if(waveform!=::waveform) {
		::waveform = waveform;
		samplesSinceLastChange = 0;
	}

	if(frequency!=::frequency) {
		::frequency = frequency;
		// updating frequency will be handled by the modulator, so no need to worry about it here
		//
		samplesSinceLastChange = 0;
	}

	if(modulatorAmp!=::modulatorAmpOffset) {
		::modulatorAmpOffset = modulatorAmp;
		samplesSinceLastChange = 0;
	}

	if(modulatorSpeed!=::modSpeed) {
		::modSpeed = modulatorSpeed;
		samplesSinceLastChange = 0;
	}

	if(rythmWaitDuration!=::rythmWaitDuration) {
		::rythmWaitDuration = (int) rythmWaitDuration;
		samplesSinceLastChange = 0;
	}

	if(rythmAliveDuration!=::rythmAliveDuration) {
		::rythmAliveDuration = (int) rythmAliveDuration;
		samplesSinceLastChange = 0;
	}
}



Audio::~Audio() {
    dac->closeStream();
    delete dac;
	delete currentAudioFrame;
}


