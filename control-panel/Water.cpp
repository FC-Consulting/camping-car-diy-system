#include "Arduino.h"
#include "Water.h"

Water::Water(int pin) {
  _pin = pin;
}

String Water::cleanTitle() {
  return String("Clean water");
}

String Water::grayTitle() {
  return String("Gray water");
}

int Water::cleanLevel() {
  return random(0, 100);
}

int Water::grayLevel() {
  return random(0, 100);
}
