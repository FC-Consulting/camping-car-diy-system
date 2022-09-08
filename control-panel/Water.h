#ifndef Water_h
#define Water_h
#include "Arduino.h"
#include "Screen.h"

class Water {
  public:
    Water();
    int getClean();
    int getGray();
};

#endif
