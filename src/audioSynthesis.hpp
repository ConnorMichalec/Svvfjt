#define __LINUX_ALSA__
#include "stk/SineWave.h"
#include "stk/RtAudio.h"

using namespace stk;

class Audio {
    public:
        Audio();
        ~Audio();
        void InitializeAudiostream();
		StkFloat FetchNextAudioFrame();
		StkFloat GetCurrentAudioFrame();
		long *GetCurrentAudioFrameIndex();
		void ReceiveNewControlParameters(float a, float b, float c);

    private:
        RtAudio *dac;
		StkFloat *currentAudioFrame;
		long *audioFrameIndex;					// amount of audio frames accumulated in total so far

		SineWave *testSineTone;
};