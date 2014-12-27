#define NUM_LEDS 50

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

