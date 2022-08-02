#ifndef Config_h
#define Config_h
#include "Arduino.h"
#include "SD.h"

class Config {
  public:
    Config();
    void begin(int spi_pin);
    String getString(const __FlashStringHelper * key);
    bool getBoolean(const __FlashStringHelper * key);
    int getInt(const __FlashStringHelper * key);
    float getFloat(const __FlashStringHelper * key);
  private:
    int SD_findKey(const __FlashStringHelper * key, char * value);
    int HELPER_ascii2Int(char *ascii, int length);
    float HELPER_ascii2Float(char *ascii, int length);
    String HELPER_ascii2String(char *ascii, int length);
};

#endif
