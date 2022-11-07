#include "Arduino.h"
#include "Electricity.h"

/* Constructor */

Electricity::Electricity() {
}

/* Publics */

int Electricity::value() {
  return random(0, 100);
}

/* Privates */
