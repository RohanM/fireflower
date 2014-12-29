Hammock::Hammock(int pin) {
  _pin = pin;
  _minResistance = 50000.0;
  _maxResistance = 0;
  _hammockState = HAMMOCK_STATE_VACANT;
}

void Hammock::update() {
  float reading, resistance;
  reading = analogRead(_pin);
  resistance = this->readingToResistance(reading);
  
  _minResistance = min(_minResistance, resistance);
  _maxResistance = max(_maxResistance, resistance);
  _percentStretch = 1.0 - ((resistance - _minResistance) / (_maxResistance - _minResistance));

  Serial.print("Percent of stretch: "); 
  Serial.println(_percentStretch * 100.0);
}

float Hammock::readingToResistance(float reading) {
  // TODO: Single return
  reading = (1023 / reading)  - 1;
  reading = HAMMOCK_SERIES_RESISTANCE / reading;
  return reading;
}

void Hammock::updateState() {
  switch (_hammockState) {
    case HAMMOCK_STATE_VACANT: 
        //ledStrips[0].setColour(CRGB(255, 0, 0));
        if (_percentStretch > 0.65) { // Transition only if stretched significantly
          _hammockState = HAMMOCK_STATE_IN_USE;
          // Entry activities for HAMMOCK_STATE_IN_USE
          //inStateCounter = 0;
        }
      break;
    case HAMMOCK_STATE_IN_USE: 
        //ledStrips[0].setColour(CRGB(0, 255, (int)(percentStretch * 50.0)) );
        if (_percentStretch < 0.35) { // Transition only if relaxed significantly
          _hammockState = HAMMOCK_STATE_VACANT;
          // Entry activities for HAMMOCK_STATE_VACANT
          //inStateCounter = 0;
        }
      break;
  }
}
