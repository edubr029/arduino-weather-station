#include <DHT.h>

// Configuring the DHT sensor
#define DHTPIN 6            // Digital pin connected to the DHT sensor

// Uncomment whatever type of DHT you're using!
#define DHTTYPE DHT11        // DHT 11
// #define DHTTYPE DHT22           // DHT 22  (AM2302)

DHT dht_s(DHTPIN, DHTTYPE); // Initialize DHT sensor for normal 16mhz Arduino

namespace dht {
  void check();

  void start(){
    dht_s.begin();
    check();
  }

  void check(){
    // Check if any reads failed and exit early (to try again).
    if (isnan(dht_s.readTemperature()) || isnan(dht_s.readHumidity())) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }
  }

  int humidity(){
    return dht_s.readHumidity();
  }

  int temperature(){
    return dht_s.readTemperature();
  }

  float heat_index(){
    // Compute heat index in Celsius (isFahreheit = false)
    return dht_s.computeHeatIndex(dht_s.readTemperature(), dht_s.readHumidity(), false);
  }
}

void serialDHT(){
  Serial.print("Humidity: ");
  Serial.print(dht::humidity());
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(dht::temperature());
  Serial.println(" *C ");

  Serial.print("Heat index: ");
  Serial.print(dht::heat_index());
  Serial.println("°C");

  delay(500);
}