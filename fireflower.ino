#include <FastLED.h>
#include "includes.h"

#define NUM_STRIPS 5

#define LED_PIN_0 2
#define LED_PIN_1 3
#define LED_PIN_2 4
#define LED_PIN_3 5
#define LED_PIN_4 6

#define MAX_LED_FILL 255


LedStrip ledStrips[NUM_STRIPS];
int clock;
Hammock hammock;
int ledFillCount;

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
  ledFillCount = 0;

  Serial.begin(9600);
}


void loop() {
  clock++;
  
  hammock.update();
  
  updateLedFillCount();
  
  ledStrips[0].spread(clock, ledFillRatio());
  
  FastLED.show();
  
  //delay(100);
}


void updateLedFillCount() {
  ledFillCount += (hammock.state() == HAMMOCK_STATE_IN_USE ? 1 : -1);
  ledFillCount = constrain(ledFillCount, 0, MAX_LED_FILL);
}


float ledFillRatio() {
  return (float)ledFillCount / (float)MAX_LED_FILL;
}
