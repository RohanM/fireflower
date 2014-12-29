#define NUM_LEDS 50

#define HAMMOCK_SERIES_RESISTANCE 10000

#define HAMMOCK_STATE_VACANT 0
#define HAMMOCK_STATE_IN_USE 1


class LedStrip {
 public:
  static void clear() { FastLED.clear(); };
  
  void init(int index);
  void setLevel(int level);
  void spread(int level, int counter);
  void setColour(CRGB colour);
  CRGB* leds();

 private:
  int _index;
  CRGB _leds[NUM_LEDS];
  CRGB _colour;
};


class Hammock {
 public:
  Hammock(int pin);
  void update();

 private:
  float readingToResistance(float reading);
  void updateState();

  int _pin;
  float _maxReading;
  float _minReading;
  float _percentReading;
  float _percentStretch;
  int _hammockState;
};

