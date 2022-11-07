#include <Arduino.h>

#define SERIAL_SPEED 115200

#define WATER_CLEAN_PIN 9
#define WATER_GRAY_PIN 10

#include "Screen.h"
#include "Sd.h"
#include "Config.h"
#include "Translation.h"
#include "Control.h"
#include "Electricity.h"
#include "Gas.h"
#include "Water.h"

Screen screen;
Sd sd(screen);
Config config(sd);
Translation translation(sd);
Control control;
Electricity electricity;
Gas gas;
Water water;

void setup() {
  Serial.begin(SERIAL_SPEED);
  while (!Serial) {
    ;
  }

  screen.init();
  sd.begin();
  config.read();
  translation.setLanguage(config.language());

  /* Welcome */
  screen.printCenter(translation.getLabel(F("welcome")));
  screen.wait(5000, 3, false);

/*
  Serial.println(config.getString(F("test")));
  Serial.println(translation.getLabel(F("welcome")));
  Serial.println(translation.getLabel(F("error_sd_load")));
*/
}

int cpt = 0;

void loop() {
  cpt++;

  switch (cpt) {
    case 1:
      screen.clear();
      screen.printTitle(translation.getLabel(F("clean_water")), 0, 0);
      screen.printProgressBar(random(0, 100), 1, config.showPercentage());
      screen.printTitle(translation.getLabel(F("gray_water")), 2, 0);
      screen.printProgressBar(random(0, 100), 3, config.showPercentage());
      break;
    case 2:
      screen.clear();
      screen.printTitle(translation.getLabel(F("gas_cylender")), 0, 0);
      screen.printProgressBar(gas.value(), 1, config.showPercentage());
      screen.printTitle(translation.getLabel(F("battery")), 2, 0);
      screen.printProgressBar(electricity.value(), 3, config.showPercentage());
      break;
    default:
      cpt = 0;
      break;
  }

  delay(config.tempo());
}
