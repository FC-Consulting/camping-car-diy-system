#ifndef Sd_h
#define Sd_h
#include "Arduino.h"
#include "Screen.h"
#include "SD.h"

class Sd {
  public:
    Sd(Screen);
    void begin();
    String getString(String, const __FlashStringHelper * key);
    bool getBoolean(String, const __FlashStringHelper * key);
    int getInt(String, const __FlashStringHelper * key);
    float getFloat(String, const __FlashStringHelper * key);
  private:
    Screen* _screen;
    int SD_findKey(String, const __FlashStringHelper * key, char * value);
    int HELPER_ascii2Int(char *ascii, int length);
    float HELPER_ascii2Float(char *ascii, int length);
    String HELPER_ascii2String(char *ascii, int length);
};

#endif
