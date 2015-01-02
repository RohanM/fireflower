void LedStrip::init(int index) {
  this->_index = index;
  this->_colour = CRGB(255, 255, 255);
}

CRGB* LedStrip::leds() {
  return this->_leds;
}

void LedStrip::setLevel(int level) {
  this->clear();
  for(int i=0; i < level; i++) {
    this->_leds[i] = this->_colour;
  }
}

void LedStrip::spread(int clock, float fillLevel) {
  for(int i=0; i < NUM_LEDS; i++) {
    this->_leds[i] = CRGB(clock % 255, 0, 0);
  }
  // When hammock unoccupied, wavey red, pulsing. Moving sine wave which modulates brightness between ~ 50 to 155.
  // When state changes to in use, green colour creeps in from one end and gradually fills the whole strip.
  // Also, the brightness grows up to 100 to 255.

  // Params: clock, levelFilled


  /*
  for(int i=0; i < NUM_LEDS; i++) { //(int) ((sin(i / NUM_LEDS * 6.28) + 1.0) / 2.0) * 255.0
    float percentOfLeds = (float)i / (float)NUM_LEDS;


    //float brightness = ( rangeSinToOne(cos(percentOfLeds * 6.28 * 4.0 + 3.14 + ((float)counter) / 10.0)) * 155.0 + 100.0;

    float brightness = ( cos(percentOfLeds * 6.28 * 4.0 + 3.14 + ((float)counter) / 10.0)) + 1.0 / 2.0 * 155.0 + 100.0;
    this->_leds[i] = CHSV(100, 200 + (int)((float)i / (float)NUM_LEDS * 55.0), (int)brightness);
  }
  */
}

/*
void LedStrip::rangeSinToOne(float in) {
  return (in + 1.0) / 2.0;
}
*/

void LedStrip::setColour(CRGB colour) {
  this->_colour = colour;
}

