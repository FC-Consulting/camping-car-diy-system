#ifndef Translation_h
#define Translation_h
#include "Arduino.h"
#include "Sd.h"

class Translation {
  public:
    Translation(Sd);
    void setLanguage(String);
    String getLabel(const __FlashStringHelper * key);
  private:
    Sd* _sd;
    String _language;
};

#endif
