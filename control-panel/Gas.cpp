#include "Arduino.h"
#include "Gas.h"

Gas::Gas(int pin) {
  _pin = pin;
}

String Gas::title() {
  return String("Gas");
}

int Gas::value() {
  return random(0, 13) * 100 / 24;
}
