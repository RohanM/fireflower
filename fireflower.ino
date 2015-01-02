#include <FastLED.h>
#include "includes.h"

#define NUM_STRIPS 5

#define LED_PIN_0 2
#define LED_PIN_1 3
#define LED_PIN_2 4
#define LED_PIN_3 5
#define LED_PIN_4 6




LedStrip ledStrips[NUM_STRIPS];
int clock;
//int inStateCounter;
Hammock hammock;

void setup() {
  for(int i=0; i<NUM_STRIPS; i++) {
    ledStrips[i].init(i);
  }
  
  // This breaks encapsulation. But the pin must be set at compile time, so
  // I do not know of a way of avoiding this :(
  FastLED.addLeds<WS2811, LED_PIN_0, BRG>(ledStrips[0].leds(), NUM_LEDS);
  FastLED.addLeds<WS2811, LED_PIN_1, BRG>(ledStrips[1].leds(), NUM_LEDS);
  FastLED.addLeds<WS2811, LED_PIN_2, BRG>(ledStrips[2].leds(), NUM_LEDS);
  FastLED.addLeds<WS2811, LED_PIN_3, BRG>(ledStrips[3].leds(), NUM_LEDS);
  FastLED.addLeds<WS2811, LED_PIN_4, BRG>(ledStrips[4].leds(), NUM_LEDS);

  LedStrip::clear();
  
  hammock.init(A0);
  
  clock = 0;
  //inStateCounter = 0;

  Serial.begin(9600);
}


void loop() {
  //float reading;
  clock++;
  //inStateCounter++;
  
  
  hammock.update();
  
  if(hammock.state() == HAMMOCK_STATE_IN_USE) {
    ledStrips[0].setColour(CRGB(0, 255, 0));
  } else {
    ledStrips[0].setColour(CRGB(255, 0, 0));
  }

  ledStrips[0].setLevel(50);

  //ledStrips[0].setLevel((int)( ( (sin(inStateCounter) + 1.0 ) * 0.5) * 50.0));
  
  //ledStrips[0].spread(clock, 0);
  
  FastLED.show();
  
  //delay(100);
}

