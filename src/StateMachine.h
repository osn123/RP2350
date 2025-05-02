#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 1
#define BRIGHTNESS 2

class StateMachine {
  enum State {
    ST_INIT,
    ST_RED,
    ST_GREEN,
    ST_BLUE,
    ST_WHITE
  };

  CRGB* leds;
  unsigned long interval;
  State state;
  unsigned long prevMillis;
  uint8_t colorRepeat;
  uint8_t repeatCount;
  int pin;

  void setColor(uint8_t r, uint8_t g, uint8_t b);
  bool checkInterval(unsigned long now);

public:
  StateMachine(int pin, unsigned long intervalMs, uint8_t repeat = 2);
  void update();
  ~StateMachine();
};

#endif

