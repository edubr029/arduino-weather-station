#include <LiquidCrystal.h>
#include "customChars.h"

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd_d(rs, en, d4, d5, d6, d7);

#define PWM_PIN 9

void customChars();

namespace lcd{
  void start(){
    // initialize LCD and set up the number of columns and rows:
    lcd_d.begin(16, 2);
    
    Serial.begin(9600);
    Wire.begin();

    lcd_d.clear();
    customChars();
  }

  void blank(int chars){
    for(int i = 0; i < chars; i++)
      lcd_d.write(byte(20));
  }
}

void customChars(){
    // Menu Arrows
    lcd_d.createChar(0, leftArrow);
    lcd_d.createChar(1, rightArrow);

    // DHT Icons
    lcd_d.createChar(2, waterDrop);
    lcd_d.createChar(3, thermometer);
}

namespace arrow{
  void left(){
      lcd_d.setCursor(0,1);
      lcd_d.write(byte(0));
  }

  void right(){
      lcd_d.setCursor(15,1);
      lcd_d.write(byte(1));
  }

  void both(){
      right();
      left();
  }

  void blink(int side){
    // 0 - left arrow | 1 - right arrow
      switch(side){
          case 0:
              left();
              delay(500);
              lcd_d.setCursor(0,1);
              lcd::blank(1);
              delay(500);
          break;
          case 1:
              right();
              delay(500);
              lcd_d.setCursor(15,1);
              lcd::blank(1);
              delay(500);
          break;
      }
  }
}