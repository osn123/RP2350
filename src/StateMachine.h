// StateMachine.h
#include <Arduino.h>

class StateMachine {
  enum State {
    ST_INIT,
    ST_LED_ON,
    ST_LED_OFF
  };

  int ledPin;
  unsigned long interval;
  State state;
  unsigned long prevMillis;

public:
  StateMachine(int pin, unsigned long intervalMs)
    : ledPin(pin), interval(intervalMs), state(ST_INIT), prevMillis(0) {
    pinMode(ledPin, OUTPUT);
  }

  void update() {
    unsigned long now = millis();
    switch (state) {
      case ST_INIT:
        digitalWrite(ledPin, LOW);
        state = ST_LED_ON;
        prevMillis = now;

        break;
      case ST_LED_ON:
        if (now - prevMillis >= interval) {
          digitalWrite(ledPin, HIGH);
          state = ST_LED_OFF;
          prevMillis = now;
        }
        break;
      case ST_LED_OFF:
        if (now - prevMillis >= interval) {
          digitalWrite(ledPin, LOW);
          state = ST_LED_ON;
          prevMillis = now;
        }
        break;
    }
  }
};

