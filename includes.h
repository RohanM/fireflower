#define NUM_LEDS 50

#define HAMMOCK_DYNAMIC_CALIBRATION true
#define HAMMOCK_SERIES_RESISTANCE 10000

#define HAMMOCK_STATE_VACANT 0
#define HAMMOCK_STATE_IN_USE 1

class LedStrip {
 public:
  static void clear() { FastLED.clear(); };
  
  void init(int index);
  void setLevel(int level);
  void spread(int clock, float fillLevel);
  void setColour(CRGB colour);
  CRGB* leds();

 private:
  int _index;
  CRGB _leds[NUM_LEDS];
  CRGB _colour;

  float scaleSinToOne(float in);
  float scaleClockToRads(int clock, int period);
};


class Hammock {
 public:
  void init(int pin);
  void update();
  int state() { return _hammockState; };

 private:
  float readingToResistance(float reading);
  void updateStretch(float resistance);
  void updateState();

  int _pin;
  float _minResistance;
  float _maxResistance;
  float _percentStretch;
  int _hammockState;
};

