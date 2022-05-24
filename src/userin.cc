/**
 * Shittily coded
 * Manage GPIO input data and make them available for audio/visual
 * Useful: https://lastminuteengineers.com/rotary-encoder-arduino-tutorial/ 
 * 
 */

#include "userin.hpp"
#include <wiringPi.h>
#include <stdio.h>
#include <iostream>

#define SELECTOR_0_PIN 2
#define SELECTOR_1_PIN 3 

#define ENCODER_PIN_A_0 4
#define ENCODER_PIN_B_0 17
int ENCODER_STATE_0 = 440;

#define ENCODER_PIN_A_1 27
#define ENCODER_PIN_B_1 22

void ENC_A_0_STATECHANGE() {
	if(digitalRead(ENCODER_PIN_A_0) == digitalRead(ENCODER_PIN_B_0)) {
		// Counterclockwise
		ENCODER_STATE_0 -= 5;
	}
	else {
		// Clockwise
		ENCODER_STATE_0 += 5;
	}
}


UserInput::UserInput() {
	// Setup wiringpi, which will handle all rpi gpio.
	wiringPiSetupGpio();

	pinMode(SELECTOR_0_PIN, INPUT);
	pinMode(SELECTOR_1_PIN, INPUT);	
	pullUpDnControl(SELECTOR_0_PIN, PUD_UP);
	pullUpDnControl(SELECTOR_1_PIN, PUD_UP);

	pinMode(ENCODER_PIN_A_0, INPUT);
	pinMode(ENCODER_PIN_B_0, INPUT);
	pullUpDnControl(ENCODER_PIN_A_0, PUD_UP);
	pullUpDnControl(ENCODER_PIN_B_0, PUD_UP);

	wiringPiISR(ENCODER_PIN_A_0, INT_EDGE_BOTH, &ENC_A_0_STATECHANGE);

	p1_state = 0;
	p2_state = ENCODER_STATE_0;
	p3_state = 0;
}

UserInput::~UserInput() {
	
}

void UserInput::Update() {

	// 3-way Selector
	if(!digitalRead(SELECTOR_0_PIN) ) {
		// Selector on left
		p1_state = 0;
	}
	else if(!digitalRead(SELECTOR_1_PIN)) {
		// Selector on right
		p1_state = 1;
	}
	else {
		// Selector in middle
		p1_state = 2;
	}

	if(ENCODER_STATE_0>0)
		p2_state = ENCODER_STATE_0;
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
