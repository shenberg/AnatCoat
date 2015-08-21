#include "FastLED.h"

// How many leds in your strip?
#define OUTLINE_NUM_LEDS 95 
#define MAN_NUM_LEDS 10

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define OUTLINE_PIN 13
#define MAN_PIN 10


// Outline structure:
// left sleeve and right sleeve are both wired to outline beginning
// left sleeve has 13 LEDs
// right sleeev 12 LEDS
// they show the same pixels as the first pixels on the outline
//
// The outline starts beneath left-front pocket, going to the rear

// Man structure:
// both sides and head wired to the same point
// both sides have 10 pixels, head has 5
// sides wired from the top (pixel 0 is topmost)

//#define CLOCK_PIN 13

// Define the array of leds
CRGB ledsOutline[OUTLINE_NUM_LEDS];
CRGB ledsMan[MAN_NUM_LEDS];

void setup() { 
	Serial.begin(57600);
	Serial.println("resetting");
	LEDS.addLeds<NEOPIXEL,OUTLINE_PIN>(ledsOutline,OUTLINE_NUM_LEDS);
	LEDS.addLeds<NEOPIXEL,MAN_PIN>(ledsMan,MAN_NUM_LEDS);
	LEDS.setBrightness(54);
}

void fadeall() { 
	for(int i = 0; i < OUTLINE_NUM_LEDS; i++) { ledsOutline[i].nscale8(250); } 
	for(int i = 0; i < MAN_NUM_LEDS; i++) { ledsMan[i].nscale8(250); } 		
}

void outlineWave() {
	for(int i = 0; i < OUTLINE_NUM_LEDS; i++) {
		uint8_t wave = quadwave8(millis()/13+i*11);

		// Set the i'th led to red 
		ledsOutline[i] = CHSV(i, 255, qsub8(wave,20));
	}

}

void loop() { 
	static uint8_t hue = 0;
	Serial.print("x");
/*
	for(int i = 0; i < OUTLINE_NUM_LEDS; i++) {
		// Set the i'th led to red 
		ledsOutline[i] = CHSV((i/10)*25, 255, 255);
	}
	//ledsOutline[5] = 0;*/
	outlineWave();
	for(int i = 0; i < MAN_NUM_LEDS; i++) {
		// Set the i'th led to red 
		ledsMan[i] = CHSV((i/10)*25, 255, 255);
	}
	ledsMan[2] = 0;
	FastLED.show();
	FastLED.delay(10);
	/*
	// First slide the led in one direction
	for(int i = 0; i < OUTLINE_NUM_LEDS; i++) {
		// Set the i'th led to red 
		ledsOutline[i] = CHSV(hue++, 255, 255);
		ledsMan[i % MAN_NUM_LEDS] = CHSV(hue, 255, 255);

		// Show the leds
		FastLED.show(); 
		// now that we've shown the leds, reset the i'th led to black
		// leds[i] = CRGB::Black;
		fadeall();
		// Wait a little bit before we loop around and do it again
		delay(10);
	}
	Serial.print("x");

	// Now go in the other direction.  
	for(int i = (OUTLINE_NUM_LEDS)-1; i >= 0; i--) {
		// Set the i'th led to red 
		ledsOutline[i] = CHSV(hue++, 255, 255);
		ledsMan[i % MAN_NUM_LEDS] = CHSV(hue, 255, 255);
		// Show the leds
		FastLED.show();
		// now that we've shown the leds, reset the i'th led to black
		// leds[i] = CRGB::Black;
		fadeall();
		// Wait a little bit before we loop around and do it again
		delay(10);
	}*/
}
