#include "Arduino.h"
#include "Config.h"
#include "Sd.h"

#define FILENAME "ccds/config"

Config::Config(Sd sd) {
  _sd = &sd;
}

String Config::getString(const __FlashStringHelper * key) {
  return _sd->getString(FILENAME, key);
}

boolean Config::getBoolean(const __FlashStringHelper * key) {
  return _sd->getBoolean(FILENAME, key);
}
