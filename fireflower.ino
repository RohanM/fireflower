#include <FastLED.h>
#include "includes.h"

#define NUM_STRIPS 5

#define LED_PIN_0 2
#define LED_PIN_1 3
#define LED_PIN_2 4
#define LED_PIN_3 5
#define LED_PIN_4 6




LedStrip ledStrips[NUM_STRIPS];
int counter;
int inStateCounter;

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
  counter = 0;
  inStateCounter = 0;
  

  
  Serial.begin(9600);
}


void loop() {
  float reading;
  counter++;
  inStateCounter++;
  



  
  //ledStrips[0].setLevel((int)( ( (sin(inStateCounter) + 1.0 ) * 0.5) * 50.0));
  
  ledStrips[0].spread(128, counter);
  FastLED.show();
  
  // CHSV(1, 255, 255)

  delay(100);
  /*
  for(int i=0; i < NUM_STRIPS; i++) {
    int proximity = sonarArray.proximity(i);

    ledStrips[i].moveAndIntensify();
    ledStrips[i].setBottomValue(proximity, allProximitiesClose);
  }
  FastLED.show();
  */
}

