#include "Arduino.h"
#include "Electricity.h"

Electricity::Electricity() {
}

String Electricity::title() {
  return String("Battery");
}

int Electricity::value() {
  return random(0, 100);
}
