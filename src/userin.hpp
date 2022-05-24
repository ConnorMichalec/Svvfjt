#pragma once

class UserInput {
	public:
		UserInput();
		~UserInput();
		void Update();
		float FetchP1();
		float FetchP2();
		float FetchP3();
		float FetchP4();
		float FetchP5();
		float FetchP6();

	private:
		// Each parameter is assigned to a different control switch
		float p1_state;	// Waveform
		float p2_state;	// Frequency
		float p3_state;	// Mod amplitude
		float p4_state;	// Mod speed
		float p5_state;	// Rythm wait duration
		float p6_state;	// Rythm alive duration 
};
