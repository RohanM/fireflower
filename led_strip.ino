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


// When hammock unoccupied, wavey red, pulsing. Moving sine wave which modulates brightness between ~ 50 to 155.
// When state changes to in use, green colour creeps in from one end and gradually fills the whole strip.
// Also, the brightness grows up to between 100 and 255.
void LedStrip::spread(int clock, float fillLevel) {
  int fillCount = fillLevel * NUM_LEDS;
  float hue, value;

  for(int i=0; i < NUM_LEDS; i++) {
    value = scaleSinToOne(sin(scaleClockToRads(clock+i, 100)));
    
    // Hue level: 25 by default. When it's reached by the fill level, it increases linearly
    //            to 90 over 20% of NUM_LEDS.

    hue = (fillCount - i) / 10.0; // hue scaled 0-1, unconstrained
    hue = constrain(hue, 0.0, 1.0);
    hue = hue * 65 + 25;
    value = value * 155.0 + 100.0;
    /*
    if(fillCount > i) {
      hue = 90;
      value = value * 155.0 + 100.0;
    } else {
      hue = 25;
      value = value * 105.0 + 50.0;
    }
    */
    
    this->_leds[i] = CHSV(hue, 255, value);
  }
}


float LedStrip::scaleSinToOne(float in) {
  // TODO: map
  return (in + 1.0) / 2.0;
}

float LedStrip::scaleClockToRads(int clock, int period) {
  // TODO: map
  return clock / (float)period * 2.0 * PI;
}

void LedStrip::setColour(CRGB colour) {
  this->_colour = colour;
}

