#include <Arduino.h>
#include "StateMachine.h"

StateMachine led1(25, 1000); // 4番ピン、1秒周期

void setup() {}

void loop() {
  led1.update();
}