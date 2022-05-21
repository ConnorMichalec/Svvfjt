#pragma once

#define __LINUX_ALSA__

#include "stk/RtAudio.h"
#include "stk/SineWave.h"
#include "stk/BlitSaw.h"
#include "stk/BlitSquare.h"

using namespace stk;

class Audio {
    public:
        Audio();
        ~Audio();
	void ReceiveControlParameters(int waveform, float frequency, float modulator);
        void InitializeAudiostream();
		StkFloat FetchNextAudioFrame();
		StkFloat GetCurrentAudioFrame();
		long *GetCurrentAudioFrameIndex();
		int GetCurrentWaveform();
    private:
        RtAudio *dac;
		StkFloat *currentAudioFrame;
		long *audioFrameIndex;					// amount of audio frames accumulated in total so far

		SineWave *sineTone;
		BlitSaw *sawTone;
		BlitSquare *squareTone;
};
