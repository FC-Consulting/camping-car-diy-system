#ifndef Config_h
#define Config_h
#include "Arduino.h"
#include "Sd.h"

class Config {
  public:
    Config(Sd);
    void read();
    String language();
    boolean showPercentage();
    int tempo();
  private:
    Sd* _sd;
    String _language;
    boolean _showPercentage;
    int _tempo;
};

#endif
