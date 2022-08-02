#ifndef Gas_h
#define Gas_h
#include "Arduino.h"

class Gas {
  public:
    Gas(int pin);
    String title();
    int value();
  private:
    int _pin;
};

#endif
