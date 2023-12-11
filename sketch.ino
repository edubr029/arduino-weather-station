#include <LiquidCrystal.h>
#include <RTClib.h>
#include <DHT.h>

#include "customChars.h"

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Configuring the RTC type
// RTC_DS3231 rtc;
RTC_DS1307 rtc;

// Configuring the DHT sensor
#define DHTPIN 6
// #define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  startLCD();
  startRTC();

  dht.begin();
}

void loop() {
  mainMenu();

  // Check if any reads failed and exit early (to try again).
  if (isnan(dht.readTemperature()) || isnan(dht.readHumidity())) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
}

void startLCD(){
  // initialize LCD and set up the number of columns and rows:
  lcd.begin(16, 2);
  
  Serial.begin(9600);
  Wire.begin();

  lcd.clear();
  customChars();
}

void startRTC(){
  if(!rtc.begin())
    Serial.println("RTC not found!");
  
  rtc.adjust(DateTime(__DATE__, __TIME__));
  //rtc.adjust(DateTime(2023, 12, 11, 13, 59, 10));

  delay(100);
}

void customChars(){
  // Menu Arrows
  lcd.createChar(0, leftArrow);
  lcd.createChar(1, rightArrow);

  lcd.createChar(2, waterDrop);
  lcd.createChar(3, thermometer);
}

void mainMenu(){
  showTime();
  printArrows();
  
  showHumidity();
  showTemperature();
}

void printArrows(){
  lcd.setCursor(0,1);
  lcd.write(byte(0));

  lcd.setCursor(15,1);
  lcd.write(byte(1));
}

void showHumidity(){
  int humidity = dht.readHumidity();

  lcd.setCursor(2,1);
  lcd.write(byte(2));
  lcd.print(humidity);
  lcd.print("%");
}

void showTemperature(){
  int temperature = dht.readTemperature();

  lcd.setCursor(9,1);
  lcd.write(byte(3));
  lcd.print(temperature);
  lcd.write(byte(223));
  lcd.print("C");
}

void showTime(){
  DateTime now = rtc.now();

  lcd.setCursor(10,0);
  lcd.print(now.hour());
  lcd.print(":");
  lcd.print(now.minute());
  
  delay(1000);
}