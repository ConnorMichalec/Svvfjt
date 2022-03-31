#include "audioSynthesis.hpp"

// Refer to: https://ccrma.stanford.edu/software/stk/crealtime.html


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

	testSineTone = new SineWave();
	testSineTone->setFrequency(440.0);
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

	*currentAudioFrame = testSineTone->tick();




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



Audio::~Audio() {
    dac->closeStream();
    delete dac;
	delete currentAudioFrame;
}


