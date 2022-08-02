#ifndef Water_h
#define Water_h
#include "Arduino.h"

class Water {
  public:
    Water(int pin);
    String cleanTitle();
    String grayTitle();
    int cleanLevel();
    int grayLevel();
  private:
    int _pin;
};

#endif
