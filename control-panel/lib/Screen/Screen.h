#ifndef Screen_h
#define Screen_h
#include "Arduino.h"
#include "LiquidCrystal_I2C.h"

class Screen {
  public:
    Screen();
    void init();
    void clear();
    void printTitle(String, int, int);
    void printProgressBar(byte, int, boolean);
    void printCenter(String);
    void wait(int, int, boolean);
  private:
    String _delimiter;
    void draw_progressbar(byte, int, boolean);
};

#endif
