#include "Arduino.h"
#include "Gas.h"

/* Constructor */

Gas::Gas() {
}

/* Publics */

int Gas::value() {
  return random(0, 13) * 100 / 24;
}

/* Privates */
