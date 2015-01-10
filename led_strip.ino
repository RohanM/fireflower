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
  float effect, hue, value;

  for(int i=0; i < EFFECT_NUM_LEDS; i++) {
    // Effect ranges from 0 to 1, based on fillCount.
    effect = (fillCount - i) / 10.0;
    effect = constrain(effect, 0.0, 1.0);
    
    // Hue level: 25 by default. When it's reached by the fill level, it increases linearly
    //            to 90 over 20% of NUM_LEDS (10 LEDs).
    hue = effect * 65 + 25;
    
    // Value consists of a sine wave, which is scaled to (50..155) when the effect is disabled,
    // and to (100..255) when the effect is enabled.
    value = scaleSinToOne(sin(scaleClockToRads(clock+i, 100)));
    value = value * (effect * 50.0 + 105.0) + (effect * 50.0 + 50.0);
    
    this->_leds[i] = CHSV(hue, 255, value);
  }
}

// Mirror from the main strip onto the side branches
void LedStrip::mirror() {
  copy( 7, 39, 17);
  copy( 7, 56, 17);
  copy(25, 72, 12);
  copy(25, 84, 12);
}

void LedStrip::copy(int src, int dst, int num) {
  // Not yet working
  //memcpy(&this->_leds[src], &this->_leds[dst], num * sizeof(CRGB));

  for(int i=0; i<num; i++) {
    this->_leds[dst+i] = this->_leds[src+i];
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

