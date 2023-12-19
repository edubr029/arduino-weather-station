#include <Wire.h>

#include "lcd.h"
#include "dht.h"
#include "rtc.h"
#include "ldr.h"
#include "bmp.h"
#include "btn.h"

// Functions Prototypes
void showHumidity();
void showTemperature();
void showTime();
void showLux();
void showPressure();
void showHeatIndex();

// Menu Functions
namespace menu{
    void principal();
    void pressure();
    void lux();
    void HI();

    void main(){
        if(button::left()){
            pressure();
        } else if(button::right()){
            lux();
        } else if(button::select()){
            HI();
        } else {
            principal();
        }
    }

    void principal(){
      lcd_d.clear();
      arrow::both();
      showTime();
      showHumidity();
      showTemperature();
    }
    
    void pressure(){
      arrow::blink(0);
      lcd_d.clear();
      arrow::both();
      showPressure();
    }

    void lux(){
      arrow::blink(1);
      lcd_d.clear();
      arrow::both();
      showLux();
    }
    
    void HI(){
      arrow::blink(0);
      arrow::blink(1);
      lcd_d.clear();
      arrow::both();
      showHeatIndex();
    }
}

// Station Functions
void showHumidity(){
    lcd_d.setCursor(1,0);
    lcd_d.print("Humidity: ");
    lcd_d.print(dht::humidity());
    lcd_d.print("%");
}

void showTemperature(){
    lcd_d.setCursor(1,1);
    lcd_d.print("Temperature: ");
    lcd_d.print(dht::temperature());
    lcd_d.print("C");
}

void showTime(){
  lcd_d.setCursor(10,0);
  rtc::clock();

  delay(1000);
}

void showLux(){
    lcd_d.setCursor(1,1);
    lcd_d.print("Lux: ");
    lcd_d.print(ldr::lux());
}

void showPressure(){
    lcd_d.setCursor(1,0);
    lcd_d.print("Pressure: ");
    lcd_d.print(bmp::pressure());
    lcd_d.print("Pa");
}

void showHeatIndex(){
    lcd_d.setCursor(1,0);
    lcd_d.print("HI: ");
    lcd_d.print(dht::heat_index());
    lcd_d.write(byte(223)); // Degree Symbol
    lcd_d.print("C");

}

// Arduino Default Functions
void setup() {
    lcd::start();
    dht::start();
    // bmp::start();
    rtc::start(0);  // 0 - Set the RTC with the current date and time
                    // 1 - Set the RTC with a specific date and time

    button::start();
}

void loop() {
    menu::main();

    serialRTC();
}