#include <RTClib.h>

// Configuring the RTC type
// Uncomment whatever type of RTC you're using!
RTC_DS3231 RTC;  // RTC DS3231
// RTC_DS1307 RTC;     // RTC DS1307

namespace rtc{
  void start(int config){
    if(!RTC.begin())
      Serial.println("RTC not found!");
    
    switch(config){
      case 0:
        RTC.adjust(DateTime(__DATE__, __TIME__));
      break;
      case 1:
        RTC.adjust(DateTime(2023, 12, 13, 13, 8, 10));
      break;
      default:
        Serial.println("Invalid RTC configuration!");
    }

    delay(100);
  }

  void clock(){
    DateTime now = RTC.now();

    int hour   = now.hour();
    int minute = now.minute();
    int second = now.second();
    
    if(hour < 10)
      lcd_d.print("0");
    lcd_d.print(hour, DEC);
    lcd_d.print(":");
    if(minute < 10)
      lcd_d.print("0");
    lcd_d.print(minute, DEC);
  }

  void date(){
    DateTime now = RTC.now();

    int day   = now.day();
    int month = now.month();

    if(day < 10)
      lcd_d.print("0");
    lcd_d.print(day);
    lcd_d.print(".");
    if(month < 10)
      lcd_d.print("0");
    lcd_d.print(month);
  }

  void weekDay(){
    DateTime now = RTC.now();

    char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    
    lcd_d.print(daysOfTheWeek[now.dayOfTheWeek()]);
  }
}

void serialRTC(){
  DateTime now = RTC.now();

  char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  
  // Serial.print(" since midnight 1/1/1970 = ");
  // Serial.print(now.unixtime());
  // Serial.print("s = ");
  // Serial.print(now.unixtime() / 86400L);
  // Serial.println("d");
  
  // // calculate a date which is 7 days and 30 seconds into the future
  // DateTime future (now + TimeSpan(7,12,30,6));
  
  // Serial.print(" now + 7d + 30s: ");
  // Serial.print(future.year(), DEC);
  // Serial.print('/');
  // Serial.print(future.month(), DEC);
  // Serial.print('/');
  // Serial.print(future.day(), DEC);
  // Serial.print(' ');
  // Serial.print(future.hour(), DEC);
  // Serial.print(':');
  // Serial.print(future.minute(), DEC);
  // Serial.print(':');
  // Serial.print(future.second(), DEC);
  // Serial.println();
  
  // Serial.println();
  // delay(3000);
}