#include "Arduino.h"
#include "Screen.h"
#include "LiquidCrystal_I2C.h"

#define LCD_NB_ROWS 4
#define LCD_NB_COLUMNS 20

LiquidCrystal_I2C lcd(0x27, LCD_NB_COLUMNS, LCD_NB_ROWS);

/* Caractères personnalisés */
byte START_DIV_0_OF_1[8] = {B01111,B11000,B10000,B10000,B10000,B10000,B11000,B01111}; // Char début 0 / 1
byte START_DIV_1_OF_1[8] = {B01111,B11000,B10011,B10111,B10111,B10011,B11000,B01111}; // Char début 1 / 1
byte DIV_0_OF_2[8]       = {B11111,B00000,B00000,B00000,B00000,B00000,B00000,B11111}; // Char milieu 0 / 2
byte DIV_1_OF_2[8]       = {B11111,B00000,B11000,B11000,B11000,B11000,B00000,B11111}; // Char milieu 1 / 2
byte DIV_2_OF_2[8]       = {B11111,B00000,B11011,B11011,B11011,B11011,B00000,B11111}; // Char milieu 2 / 2
byte END_DIV_0_OF_1[8]   = {B11110,B00011,B00001,B00001,B00001,B00001,B00011,B11110}; // Char fin 0 / 1
byte END_DIV_1_OF_1[8]   = {B11110,B00011,B11001,B11101,B11101,B11001,B00011,B11110}; // Char fin 1 / 1

/* Constructor */

Screen::Screen() {
  _delimiter = "|";
}

/* Publics */

void Screen::init() {
  lcd.init();
  lcd.backlight();
  
  lcd.createChar(0, START_DIV_0_OF_1);
  lcd.createChar(1, START_DIV_1_OF_1);
  lcd.createChar(2, DIV_0_OF_2);
  lcd.createChar(3, DIV_1_OF_2);
  lcd.createChar(4, DIV_2_OF_2);
  lcd.createChar(5, END_DIV_0_OF_1);
  lcd.createChar(6, END_DIV_1_OF_1);
}

void Screen::clear() {
  lcd.clear();
}

void Screen::printTitle(String title, int line, int column) {
  lcd.setCursor(column, line);
  lcd.print(title);
}

void Screen::printProgressBar(byte value, int line, boolean withValue) {
  draw_progressbar(value, line, withValue);
}

void Screen::printCenter(String value) {
  Serial.println(value);
  int cursorOffset = 0;

  int LineCount = 0;
  String lines[4];

  while (value.length() > 0) {
    int index = value.indexOf(_delimiter);
    if (index == -1) {
      lines[LineCount++] = value;
      break;
    } else {
      lines[LineCount++] = value.substring(0, index);
      value = value.substring(index+1);
    }
    Serial.println(lines[LineCount]);
  }

  for (int i = 0; i < LineCount; i++) {
    cursorOffset = ( LCD_NB_COLUMNS - lines[i].length() ) / 2;
    lcd.setCursor(cursorOffset, i);
    lcd.print(lines[i]);
  }
}

void Screen::wait(int sec, int line, boolean undo) {
  
  int tmpDelay = sec / 100;

  if (undo) {
    for (int w = 100; w > 0; w--) {
      draw_progressbar(w, line, false);
      delay(tmpDelay);
    }
  } else {
    for (int w = 0; w < 100; w++) {
      draw_progressbar(w, line, false);
      delay(tmpDelay);
    }
  }
  
  lcd.setCursor(0, line);
  lcd.print("");
}

/* Privates */

void Screen::draw_progressbar(byte percent, int line, boolean withValue) {
  int cols = LCD_NB_COLUMNS;
  if (withValue) {
    cols -= 5;
  }
  
  lcd.setCursor(0, line);
 
  byte nb_columns = map(percent, 0, 100, 0, cols * 2 - 2);

  for (byte i = 0; i < cols; ++i) {
    if (i == 0) {
      if (nb_columns > 0) {
        lcd.write(1); // Char début 1 / 1
        nb_columns -= 1;
      } else {
        lcd.write((byte) 0); // Char début 0 / 1
      }

    } else if (i == cols -1) {
      if (nb_columns > 0) {
        lcd.write(6); // Char fin 1 / 1
      } else {
        lcd.write(5); // Char fin 0 / 1
      }
    } else {
      if (nb_columns >= 2) {
        lcd.write(4); // Char div 2 / 2
        nb_columns -= 2;
      } else if (nb_columns == 1) {
        lcd.write(3); // Char div 1 / 2
        nb_columns -= 1;
      } else {
        lcd.write(2); // Char div 0 / 2
      }
    }
  }

  if (withValue) {
    lcd.setCursor(cols + 4 - ((String) percent).length(), line);
    lcd.print(percent);
    lcd.setCursor(LCD_NB_COLUMNS - 1, line);
    lcd.print("%");
  }
}
