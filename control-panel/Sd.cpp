#include "Arduino.h"
#include "Sd.h"
#include "Screen.h"
#include "SPI.h"
#include "SD.h"

#define KEY_MAX_LENGTH    30 // change it if key is longer
#define VALUE_MAX_LENGTH  30 // change it if value is longer

File myFile;

Sd::Sd(Screen screen) {
  _screen = &screen;
}

void Sd::begin(int spi_pin) {
  if (!SD.begin(spi_pin)) {
    _screen->clear();
    _screen->printTitle(F("Erreur lecteur SD"), 0, 0);
    _screen->printTitle(F("ou"), 1, 0);
    _screen->printTitle(F("Carte SD non present"), 2, 0);
    while (1); // don't do anything more:
  }
}

String Sd::getString(String filename, const __FlashStringHelper * key) {
  char value_string[VALUE_MAX_LENGTH];
  int value_length = SD_findKey(filename, key, value_string);
  return HELPER_ascii2String(value_string, value_length);
}

bool Sd::getBoolean(String filename, const __FlashStringHelper * key) {
  char value_string[VALUE_MAX_LENGTH];
  int value_length = SD_findKey(filename, key, value_string);
  return value_length > 0;
}

int Sd::getInt(String filename, const __FlashStringHelper * key) {
  char value_string[VALUE_MAX_LENGTH];
  int value_length = SD_findKey(filename, key, value_string);
  return HELPER_ascii2Int(value_string, value_length);
}

float Sd::getFloat(String filename, const __FlashStringHelper * key) {
  char value_string[VALUE_MAX_LENGTH];
  int value_length = SD_findKey(filename, key, value_string);
  return HELPER_ascii2Float(value_string, value_length);
}

int Sd::SD_findKey(String filename, const __FlashStringHelper * key, char * value) {
  File configFile = SD.open(filename, FILE_READ);

  if (!configFile) {
    _screen->clear();
    _screen->printTitle("SD Card", 0, 0);
    _screen->printTitle(String("Err opening file"), 1, 0);
    _screen->printTitle(filename, 2, 0);
    _screen->wait(5000, 3, true);
    return;
  }

  char key_string[KEY_MAX_LENGTH];
  char SD_buffer[KEY_MAX_LENGTH + VALUE_MAX_LENGTH + 1]; // 1 is = character
  int key_length = 0;
  int value_length = 0;

  // Flash string to string
  PGM_P keyPoiter;
  keyPoiter = reinterpret_cast<PGM_P>(key);
  byte ch;
  do {
    ch = pgm_read_byte(keyPoiter++);
    if (ch != 0)
      key_string[key_length++] = ch;
  } while (ch != 0);

  // check line by line
  while (configFile.available()) {
    int buffer_length = configFile.readBytesUntil('\n', SD_buffer, 100);
    if (SD_buffer[buffer_length - 1] == '\r')
      buffer_length--; // trim the \r

    if (buffer_length > (key_length + 1)) { // 1 is = character
      if (memcmp(SD_buffer, key_string, key_length) == 0) { // equal
        if (SD_buffer[key_length] == '=') {
          value_length = buffer_length - key_length - 1;
          memcpy(value, SD_buffer + key_length + 1, value_length);
          break;
        }
      }
    }
  }

  configFile.close();  // close the file
  return value_length;
}

int Sd::HELPER_ascii2Int(char *ascii, int length) {
  int sign = 1;
  int number = 0;

  for (int i = 0; i < length; i++) {
    char c = *(ascii + i);
    if (i == 0 && c == '-')
      sign = -1;
    else {
      if (c >= '0' && c <= '9')
        number = number * 10 + (c - '0');
    }
  }

  return number * sign;
}

float Sd::HELPER_ascii2Float(char *ascii, int length) {
  int sign = 1;
  int decimalPlace = 0;
  float number  = 0;
  float decimal = 0;

  for (int i = 0; i < length; i++) {
    char c = *(ascii + i);
    if (i == 0 && c == '-')
      sign = -1;
    else {
      if (c == '.')
        decimalPlace = 1;
      else if (c >= '0' && c <= '9') {
        if (!decimalPlace)
          number = number * 10 + (c - '0');
        else {
          decimal += ((float)(c - '0') / pow(10.0, decimalPlace));
          decimalPlace++;
        }
      }
    }
  }

  return (number + decimal) * sign;
}

String Sd::HELPER_ascii2String(char *ascii, int length) {
  String str;
  str.reserve(length);
  str = "";

  for (int i = 0; i < length; i++) {
    char c = *(ascii + i);
    str += String(c);
  }

  return str;
}
