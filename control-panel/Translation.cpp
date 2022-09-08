#include "Arduino.h"
#include "Translation.h"
#include "Sd.h"

#define FILENAME "ccds/lang/"

Translation::Translation(Sd sd) {
  _sd = &sd;
  _language = "en";
}

void Translation::setLanguage(String language) {
  _language = language;
}

String Translation::getLabel(const __FlashStringHelper * key) {
  return _sd->getString(String(FILENAME) + String(_language), key);
}
