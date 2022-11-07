#include "Arduino.h"
#include "Control.h"

Control::Control() {
}

String Control::title() {
  return String("Control");
}

int Control::value() {
  return random(0, 100);
}
