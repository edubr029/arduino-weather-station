#include <RTClib.h>

// Configuring the RTC type
// RTC_DS3231 rtc;
RTC_DS1307 rtc;

void startRTC(){
  if(!rtc.begin())
    Serial.println("RTC not found!");
  
  rtc.adjust(DateTime(__DATE__, __TIME__));
  //rtc.adjust(DateTime(2023, 12, 13, 13, 8, 10));

  delay(100);
}

void clockHM(){
  DateTime now = rtc.now();
  
  if(now.hour() < 10)
    lcd.print("0");
  lcd.print(now.hour(), DEC);
  lcd.print(":");
  if(now.minute() < 10)
    lcd.print("0");
  lcd.print(now.minute(), DEC);
}