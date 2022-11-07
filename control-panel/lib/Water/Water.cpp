#include "Arduino.h"
#include "Water.h"
#include "Screen.h"

/* Constructor */

Water::Water() {
}

/* Publics */

int Water::getClean() {
  return random(0, 100);
}

int Water::getGray() {
  return random(0, 100);
}

/* Privates */
