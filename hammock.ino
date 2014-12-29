Hammock::Hammock() {
  _minReading = 50000.0;
  _maxReading = 0;
  _hammockState = STATE_AMBIENT;
}

void Hammock::update() {
  float reading, resistance;
  reading = analogRead(THERMISTORPIN);
  //Serial.print("Analog reading "); 
  //Serial.println(reading);
 
  // convert the value to resistance
  resistance = this->readingToResistance(reading);
  //  Serial.print("Thermistor resistance "); 
  //  Serial.println(resistance);
  
  _maxReading = max(_maxReading, resistance);
  _minReading = min(_minReading, resistance);
  _percentReading = (resistance - _minReading) / (_maxReading - _minReading);
  _percentStretch = 1.0 - _percentReading;
  //  Serial.print("Range of resistance: "); 
  // Serial.print(_minReading);
  //  Serial.print(" to "); 
  //  Serial.println(_maxReading);
  //  Serial.print("Percent of range: "); 
  //  Serial.println(_percentReading * 100.0);
  Serial.print("Percent of stretch: "); 
  Serial.println(_percentStretch * 100.0);
}

float Hammock::readingToResistance(float reading) {
  // TODO: Single return
  reading = (1023 / reading)  - 1;
  reading = SERIESRESISTOR / reading;
  return reading;
}

void Hammock::updateState() {
  switch (_hammockState) {
    case STATE_AMBIENT: 
        //ledStrips[0].setColour(CRGB(255, 0, 0));
        if (_percentStretch > 0.65) { // Transition only if stretched significantly
          _hammockState = STATE_IN_USE;
          // Entry activities for STATE_IN_USE
          //inStateCounter = 0;
        }
      break;
    case STATE_IN_USE: 
        //ledStrips[0].setColour(CRGB(0, 255, (int)(percentStretch * 50.0)) );
        if (_percentStretch < 0.35) { // Transition only if relaxed significantly
          _hammockState = STATE_AMBIENT;
          // Entry activities for STATE_AMBIENT
          //inStateCounter = 0;
        }
      break;
  }
}
