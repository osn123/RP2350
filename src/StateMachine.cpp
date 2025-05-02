#include "StateMachine.h"

StateMachine::StateMachine(int pin, unsigned long intervalMs, uint8_t repeat) {
  this->pin = pin;
  interval = intervalMs;
  colorRepeat = repeat;
  repeatCount = 0;
  state = ST_INIT;
  prevMillis = 0;

  leds = new CRGB[NUM_LEDS];
  FastLED.addLeds<WS2812B, 22, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

StateMachine::~StateMachine() {
  delete[] leds;
}

void StateMachine::update() {
  unsigned long now = millis();
  
  switch (state) {
    case ST_INIT:
      FastLED.clear();
      FastLED.show();
      state = ST_RED;
      prevMillis = now;
      break;
    case ST_RED:
      if (now - prevMillis >= interval) {
        leds[0] = CRGB(255, 0, 0);
        FastLED.show();
        state = ST_GREEN;
        prevMillis = now;
      }
      break;
    case ST_GREEN:
      if (now - prevMillis >= interval) {
        leds[0] = CRGB(0, 255, 0);
        FastLED.show();
        state = ST_BLUE;
        prevMillis = now;
      }
      break;
    case ST_BLUE:
      if (now - prevMillis >= interval) {
        leds[0] = CRGB(0, 0, 255);
        FastLED.show();
        state = ST_WHITE;
        prevMillis = now;
      }
      break;
    case ST_WHITE:
      if (now - prevMillis >= interval) {
        leds[0] = CRGB(255, 255, 255);
        FastLED.show();
        repeatCount++;
        if (repeatCount >= colorRepeat) {
          repeatCount = 0;
          state = ST_RED;
        } else {
          state = ST_INIT;
        }
        prevMillis = now;
      }
      break;
  }
} 