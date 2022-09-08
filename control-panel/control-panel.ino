/*
 * Gestion d'un camping car
 */

#define SERIAL_SPEED 115200

#define SD_CARD_SELECT 10

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
Gas gas(WATER_CLEAN_PIN);
Water water(WATER_CLEAN_PIN);

boolean showPercentage = true;

void setup() {
  Serial.begin(SERIAL_SPEED);
  while (!Serial) {
    ;
  }

  screen.init();
  sd.begin(SD_CARD_SELECT);
  translation.setLanguage(config.getString(F("language")));
  
  showPercentage = config.getBoolean(F("showPercentage"));

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
      screen.printTitle(water.cleanTitle(), 0, 0);
      screen.printProgressBar(water.cleanLevel(), 1, showPercentage);
      break;
    case 2:
      screen.clear();
      screen.printTitle(water.grayTitle(), 0, 0);
      screen.printProgressBar(water.grayLevel(), 1, showPercentage);
      break;
    case 3:
      screen.clear();
      screen.printTitle(gas.title(), 0, 0);
      screen.printProgressBar(gas.value(), 1, showPercentage);
      break;
    case 4:
      screen.clear();
      screen.printTitle(electricity.title(), 0, 0);
      screen.printProgressBar(electricity.value(), 1, showPercentage);
      break;
    default:
      cpt = 0;
      break;
  }

  delay(5000);
}
