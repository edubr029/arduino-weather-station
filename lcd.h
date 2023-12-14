#include <LiquidCrystal.h>
#include "customChars.h"

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void customChars();

void startLCD(){
  // initialize LCD and set up the number of columns and rows:
  lcd.begin(16, 2);
  
  Serial.begin(9600);
  Wire.begin();

  lcd.clear();
  customChars();
}

void customChars(){
  // Menu Arrows
  lcd.createChar(0, leftArrow);
  lcd.createChar(1, rightArrow);

  // DHT Icons
  lcd.createChar(2, waterDrop);
  lcd.createChar(3, thermometer);
}
