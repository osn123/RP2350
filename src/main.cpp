#include <Arduino.h>
#include "StateMachine.h"

#define LED_POWER 23
#define LED_PIN 22

StateMachine rgb(LED_PIN, 1000, 2); // LED_PIN, 1秒周期, 2回繰り返し

void setup() {
  pinMode(LED_POWER, OUTPUT);
  digitalWrite(LED_POWER, HIGH);
}

void loop() {
  rgb.update();
}