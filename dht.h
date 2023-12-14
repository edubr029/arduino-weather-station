#include <DHT.h>

// Configuring the DHT sensor
#define DHTPIN 6
// #define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);

void checkDHT(){
  // Check if any reads failed and exit early (to try again).
  if (isnan(dht.readTemperature()) || isnan(dht.readHumidity())) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
}