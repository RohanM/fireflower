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
// Also, the brightness grows up to 100 to 255.
void LedStrip::spread(int clock, float fillLevel) {
  for(int i=0; i < NUM_LEDS; i++) {
    float hue, value;
    
    value = scaleSinToOne(sin(scaleClockToRads(clock+i, 100)));
    value = value * 105.0 + 50.0;
    
    if(fillLevel * NUM_LEDS > i) {
      hue = 90;
    } else {
      hue = 25;
    }
    
    this->_leds[i] = CHSV(hue, 255, value);
  }
}


float LedStrip::scaleSinToOne(float in) {
  return (in + 1.0) / 2.0;
}

float LedStrip::scaleClockToRads(int clock, int period) {
  return clock / (float)period * 2.0 * PI;
}


void LedStrip::setColour(CRGB colour) {
  this->_colour = colour;
}

