#include "Arduino.h"
#include "Config.h"
#include "Sd.h"

#define FILENAME "ccds/config"

/* Constructor */

Config::Config(Sd sd) {
  _sd = &sd;
}

/* Publics */

void Config::read() {
  _language = _sd->getString(FILENAME, F("language"));
  _showPercentage= _sd->getString(FILENAME, F("showPercentage"));
  _tempo = _sd->getInt(FILENAME, F("tempo"));
}

String Config::language() {
  return _language;
}

boolean Config::showPercentage() {
  return _showPercentage;
}

int Config::tempo() {
  return _tempo;
}

/* Privates */
