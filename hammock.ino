void Hammock::init(int pin) {
  _pin = pin;
  _minResistance = 50000.0;
  _maxResistance = 0;
  _hammockState = HAMMOCK_STATE_VACANT;
}

void Hammock::update() {
  float reading, resistance;
  reading = analogRead(_pin);
  resistance = this->readingToResistance(reading);
  
  this->updateStretch(resistance);
  this->updateState();

  //Serial.print("Percent of stretch: ");
  //Serial.println(_percentStretch * 100.0);
}



float Hammock::readingToResistance(float reading) {
  return HAMMOCK_SERIES_RESISTANCE / ((1023 / reading)  - 1);
}

void Hammock::updateStretch(float resistance) {
  _minResistance = min(_minResistance, resistance);
  _maxResistance = max(_maxResistance, resistance);
  _percentStretch = 1.0 - ((resistance - _minResistance) / (_maxResistance - _minResistance));
}

void Hammock::updateState() {
  switch (_hammockState) {
    case HAMMOCK_STATE_VACANT: 
        if (_percentStretch > 0.65) { // Transition only if stretched significantly
          _hammockState = HAMMOCK_STATE_IN_USE;
          
          // Entry activities for HAMMOCK_STATE_IN_USE
        }
      break;
    case HAMMOCK_STATE_IN_USE: 
        if (_percentStretch < 0.35) { // Transition only if relaxed significantly
          _hammockState = HAMMOCK_STATE_VACANT;
          
          // Entry activities for HAMMOCK_STATE_VACANT
        }
      break;
  }
}
