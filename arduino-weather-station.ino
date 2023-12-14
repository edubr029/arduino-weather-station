#include <Wire.h>

#include "lcd.h"
#include "dht.h"
#include "rtc.h"
#include "ldr.h"

void setup() {
  startLCD();
  startRTC();

  dht.begin();
}

void loop() {
  mainMenu();
  checkDHT();
  ldr_test();
}

void mainMenu(){
  showHumidity();
  showTemperature();
  showArrows();
  showTime();
  show_lux();
}

void showArrows(){
  printRightArrow();
  printLeftArrow();
}

void printRightArrow(){
  lcd.setCursor(0,1);
  lcd.write(byte(0));
}

void printLeftArrow(){
  lcd.setCursor(15,1);
  lcd.write(byte(1));
}

void show_lux(){
  lcd.setCursor(0,0);
  lcd.print(ldr::lux());
}

void showHumidity(){
  int humidity = dht.readHumidity();

  lcd.setCursor(2,1);
  lcd.write(byte(2));
  lcd.print(humidity);
  lcd.print("%");
  lcd.print("   ");
}

void showTemperature(){
  int temperature = dht.readTemperature();

  lcd.setCursor(9,1);
  lcd.write(byte(3));
  lcd.print(temperature);
  lcd.write(byte(223));
  lcd.print("C");
  lcd.print(" ");
}

void showTime(){
  lcd.setCursor(10,0);
  clockHM();

  delay(1000);
}