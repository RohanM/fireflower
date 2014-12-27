#include <FastLED.h>
#include <math.h>
#include "includes.h"

#define NUM_STRIPS 5

#define LED_PIN_0 2
#define LED_PIN_1 3
#define LED_PIN_2 4
#define LED_PIN_3 5
#define LED_PIN_4 6

#define SERIESRESISTOR 10000
#define THERMISTORPIN A0 


LedStrip ledStrips[NUM_STRIPS];
int counter;
int inStateCounter;
float maxReading;
float minReading;
float percentReading;
float percentStretch;

#define STATE_AMBIENT 0
#define STATE_IN_USE 1
int hammockState;

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
  
  minReading = 50000.0;
  maxReading = 0;
  
  hammockState = STATE_AMBIENT;
  Serial.begin(9600);
}


void loop() {
  float reading;
  counter++;
  inStateCounter++;
  
  reading = analogRead(THERMISTORPIN);
 
  //Serial.print("Analog reading "); 
  //Serial.println(reading);
 
  // convert the value to resistance
  reading = (1023 / reading)  - 1;
  reading = SERIESRESISTOR / reading;
//  Serial.print("Thermistor resistance "); 
//  Serial.println(reading);
  
  maxReading = max(maxReading, reading);
  minReading = min(minReading, reading);
  percentReading = (reading - minReading) / (maxReading - minReading);
  percentStretch = 1.0 - percentReading;
//  Serial.print("Range of resistance: "); 
// Serial.print(minReading);
//  Serial.print(" to "); 
//  Serial.println(maxReading);
//  Serial.print("Percent of range: "); 
//  Serial.println(percentReading * 100.0);
  Serial.print("Percent of stretch: "); 
  Serial.println(percentStretch * 100.0);

  switch (hammockState) {
    case STATE_AMBIENT: 
        ledStrips[0].setColour(CRGB(255, 0, 0));
        if (percentStretch > 0.65) { // Transition only if stretched significantly
          hammockState = STATE_IN_USE;
          // Entry activities for STATE_IN_USE
          inStateCounter = 0;
        }
      break;
    case STATE_IN_USE: 
        ledStrips[0].setColour(CRGB(0, 255, (int)(percentStretch * 50.0)) );
        if (percentStretch < 0.35) { // Transition only if relaxed significantly
          hammockState = STATE_AMBIENT;
          // Entry activities for STATE_AMBIENT
          inStateCounter = 0;
        }
      break;
  }
  
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

