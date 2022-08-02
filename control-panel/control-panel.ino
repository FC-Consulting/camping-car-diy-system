/*
 * Gestion d'un camping car
 */

#define SERIAL_SPEED 115200

#define LCD_NB_ROWS 2
#define LCD_NB_COLUMNS 16
#define LCD_CONTRAST_PIN 6

#define WATER_CLEAN_PIN 9
#define WATER_GRAY_PIN 10

#include "LiquidCrystal.h"

#include "Config.h"
#include "Control.h"
#include "Electricity.h"
#include "Gas.h"
#include "Water.h"

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Config config;
Control control;
Electricity electricity;
Gas gas(WATER_CLEAN_PIN);
Water water(WATER_CLEAN_PIN);

void setup() {
  Serial.begin(SERIAL_SPEED);
  while (!Serial) {
    ;
  }

  config.begin(4);
  Serial.println(config.getString(F("Hello")));
  
  analogWrite(LCD_CONTRAST_PIN, 50);
  lcd.begin(LCD_NB_COLUMNS, LCD_NB_ROWS);
}

int cpt = 0;

void loop() {
  cpt++;

  switch (cpt) {
    case 1:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(water.cleanTitle());
      draw_progressbar(water.cleanLevel(), 1);
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(water.grayTitle());
      draw_progressbar(water.grayLevel(), 1);
      break;
    case 3:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(gas.title());
      draw_progressbar(gas.value(), 1);
      break;
    case 4:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(electricity.title());
      draw_progressbar(electricity.value(), 1);
      break;
    default:
      cpt = 0;
      break;
  }

  delay(5000);
}

void draw_progressbar(byte percent, int line) {
  lcd.setCursor(0, line);
  byte nb_columns = map(percent, 0, 100, 0, LCD_NB_COLUMNS * 5);
  for (byte i = 0; i < LCD_NB_COLUMNS; ++i) {
    if (nb_columns == 0) {
      lcd.write((byte) 0);
    } else if (nb_columns >= 5) {
      lcd.write(5);
      nb_columns -= 5;
    } else {
      lcd.write(nb_columns);
      nb_columns = 0;
    }
  }
}
