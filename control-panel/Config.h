#ifndef Config_h
#define Config_h
#include "Arduino.h"
#include "Sd.h"

class Config {
  public:
    Config(Sd);
    String getString(const __FlashStringHelper * key);
    boolean getBoolean(const __FlashStringHelper * key);
  private:
    Sd* _sd;
};

#endif
