/**
 * Manage GPIO input data and make them available for audio/visual
 * 
 */

#include "userin.hpp"
#include <wiringPi.h>

const int waveSelector0pin = 2;
const int waveSelector1pin = 3; 

UserInput::UserInput() {
	// Setup wiringpi, which will handle all rpi gpio.
	wiringPiSetupGpio();

	pinMode(waveSelector0pin, INPUT);
	pinMode(waveSelector1pin, INPUT);	
	pullUpDnControl(waveSelector0pin, PUD_UP);
	pullUpDnControl(waveSelector0pin, PUD_UP);

	p1_state = 0;
	p2_state = 0;
	p3_state = 0;
}

UserInput::~UserInput() {
	
}

void UserInput::Update() {
	if(!digitalRead(waveSelector0pin)) {
		// Selector on left
		p1_state = 0;
	}
	else if(!digitalRead(waveSelector1pin)) {
		// Selector on right
		p1_state = 1;
	}
	else {
		// Selector in middle
		p1_state = 2;
	}
}

float UserInput::FetchP1() {
	return(p1_state);
}

float UserInput::FetchP2() {
	return(p2_state);	
}

float UserInput::FetchP3() {
	return(p3_state);	
}
