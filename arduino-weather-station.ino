#include <Wire.h>

#include "lcd.h"
#include "dht.h"
#include "rtc.h"
#include "ldr.h"
#include "bmp.h"
#include "btn.h"

void showHumidity();
void showTemperature();
void showTime();

namespace arrow{
    void right(){
        lcd_d.setCursor(0,1);
        lcd_d.write(byte(0));
    }

    void left(){
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

namespace menu{
  void main(){
    if(button::left == HIGH) arrow::blink(0);
    else if(button::right == HIGH) arrow::blink(1);
    else arrow::both();

    if(button::select == HIGH) lcd_d.clear();
    else {
      showHumidity();
      showTemperature();
      showTime();
    }
  }

  void pressure(){
    lcd_d.setCursor(1,0);
    lcd_d.print(bmp::pressure());
    lcd_d.print("Pa");
  }

  void lux(){
    lcd_d.setCursor(1,1);
    lcd_d.print("Lux");
    lcd_d.print(ldr::lux());
    lcd_d.print("lx");
  }

  void HI(){
    lcd_d.setCursor(1,0);
    lcd_d.print(dht::heat_index());
    lcd_d.write(byte(223)); // Degree Symbol
    lcd_d.print("C");
  }
}

void showTime(){
  lcd_d.setCursor(10,0);
  rtc::clock();

  delay(1000);
}

void showHumidity(){
  int hum = dht::humidity();

  lcd_d.setCursor(2,1);
  lcd_d.write(byte(2));   // Water Drop
  lcd_d.print(hum);
  lcd_d.print("%");
  lcd::blank(3);
}

void showTemperature(){
  int temp = dht::temperature();
  
  lcd_d.setCursor(9,1);
  lcd_d.write(byte(3));   // Thermometer
  lcd_d.print(temp);
  // lcd_d.print((int)bmp::temperature());
  lcd_d.write(byte(223)); // Degree Symbol
  lcd_d.print("C"); 
  lcd::blank(1);
}

// Arduino Default Functions
void setup() {
  lcd::start();
  dht::start();
  // bmp::start();
  rtc::start(0); // 0 - Set the RTC with the current date and time
                 // 1 - Set the RTC with a specific date and time

  button::start();
}

void loop() {
  menu::main();
  
  // Test Functions
  // ldr_test();

  // Debug Functions
  button::debug();

  // Serial Test Functions
  // serialBMP();
  // serialDHT();
  // serialRTC();
}