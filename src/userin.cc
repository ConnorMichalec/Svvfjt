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
float ENCODER_STATE_0 = 440;

#define ENCODER_PIN_A_1 27
#define ENCODER_PIN_B_1 22
float ENCODER_STATE_1 = 0;

#define ENCODER_PIN_A_2 10
#define ENCODER_PIN_B_2 9
float ENCODER_STATE_2 = 0.0001;

#define ENCODER_PIN_A_3 5
#define ENCODER_PIN_B_3 11
float ENCODER_STATE_3 = 7000;

#define ENCODER_PIN_A_4 6
#define ENCODER_PIN_B_4 13
float ENCODER_STATE_4 = 300;


void ENC_A_0_STATECHANGE() {
	if(digitalRead(ENCODER_PIN_A_0) == digitalRead(ENCODER_PIN_B_0)) {
		// Counterclockwise
		ENCODER_STATE_0 -= 6;
	}
	else {
		// Clockwise
		ENCODER_STATE_0 += 6;
	}
}

void ENC_A_1_STATECHANGE() {
	if(digitalRead(ENCODER_PIN_A_1) == digitalRead(ENCODER_PIN_B_1)) {
		// Counterclockwise
		ENCODER_STATE_1 -= 1;
	}
	else {
		// Clockwise
		ENCODER_STATE_1 += 1;
	}
}

void ENC_A_2_STATECHANGE() {
	if(digitalRead(ENCODER_PIN_A_2) == digitalRead(ENCODER_PIN_B_2)) {
		// Counterclockwise
		ENCODER_STATE_2 -= 0.00005;
	}
	else {
		// Clockwise
		ENCODER_STATE_2 += 0.00005;
	}
}

void ENC_A_3_STATECHANGE() {
	if(digitalRead(ENCODER_PIN_A_3) == digitalRead(ENCODER_PIN_B_3)) {
		// Counterclockwise
		ENCODER_STATE_3 -= 100;
	}
	else {
		// Clockwise
		ENCODER_STATE_3 += 100;
	}
}

void ENC_A_4_STATECHANGE() {
	if(digitalRead(ENCODER_PIN_A_4) == digitalRead(ENCODER_PIN_B_4)) {
		// Counterclockwise
		ENCODER_STATE_4 -= 30;
	}
	else {
		// Clockwise
		ENCODER_STATE_4 += 30;
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


	pinMode(ENCODER_PIN_A_1, INPUT);
	pinMode(ENCODER_PIN_B_1, INPUT);
	pullUpDnControl(ENCODER_PIN_A_1, PUD_UP);
	pullUpDnControl(ENCODER_PIN_B_1, PUD_UP);
	
	wiringPiISR(ENCODER_PIN_A_1, INT_EDGE_BOTH, &ENC_A_1_STATECHANGE);
	
	
	pinMode(ENCODER_PIN_A_2, INPUT);
	pinMode(ENCODER_PIN_B_2, INPUT);
	pullUpDnControl(ENCODER_PIN_A_2, PUD_UP);
	pullUpDnControl(ENCODER_PIN_B_2, PUD_UP);
	
	wiringPiISR(ENCODER_PIN_A_2, INT_EDGE_BOTH, &ENC_A_2_STATECHANGE);


	pinMode(ENCODER_PIN_A_3, INPUT);
	pinMode(ENCODER_PIN_B_3, INPUT);
	pullUpDnControl(ENCODER_PIN_A_3, PUD_UP);
	pullUpDnControl(ENCODER_PIN_B_3, PUD_UP);
	
	wiringPiISR(ENCODER_PIN_A_3, INT_EDGE_BOTH, &ENC_A_3_STATECHANGE);


	pinMode(ENCODER_PIN_A_4, INPUT);
	pinMode(ENCODER_PIN_B_4, INPUT);
	pullUpDnControl(ENCODER_PIN_A_4, PUD_UP);
	pullUpDnControl(ENCODER_PIN_B_4, PUD_UP);
	
	wiringPiISR(ENCODER_PIN_A_4, INT_EDGE_BOTH, &ENC_A_4_STATECHANGE);
	
	
	p1_state = 0;
	p2_state = ENCODER_STATE_0;
	p3_state = ENCODER_STATE_1;
	p4_state = ENCODER_STATE_2;
	p5_state = ENCODER_STATE_3;
	p6_state = ENCODER_STATE_4;
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

	p2_state = ENCODER_STATE_0;
	p3_state = ENCODER_STATE_1;
	p4_state = ENCODER_STATE_2;
	p5_state = ENCODER_STATE_3;
	p6_state = ENCODER_STATE_4;
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

float UserInput::FetchP4() {
	return(p4_state);	
}

float UserInput::FetchP5() {
	return(p5_state);	
}

float UserInput::FetchP6() {
	return(p6_state);	
}
