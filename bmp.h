#include <Adafruit_BMP085.h>

#define seaLevelPressure_hPa 1013.25

Adafruit_BMP085 BMP;

namespace bmp{
    void start(){
        Serial.begin(9600);
        if(!BMP.begin()){
            Serial.println("Could not find a valid BMP085 sensor, check wiring!");
            while(1){}
        }
    }

    float temperature(){
        return BMP.readTemperature();
    }

    float pressure(){
        return BMP.readPressure();
    }

    float altitude(){
        return BMP.readAltitude();
    }

    float sealevel_pressure(){
        return BMP.readSealevelPressure();
    }

    float real_altitude(){
        return BMP.readAltitude(seaLevelPressure_hPa * 100); // the 100 value is to convert hPa to Pa
    }
}

void serialBMP(){
    Serial.print("Temperature = ");
    Serial.print(bmp::temperature());
    Serial.println(" *C");
    
    Serial.print("Pressure = ");
    Serial.print(bmp::pressure());
    Serial.println(" Pa");

    Serial.print("Altitude = ");
    Serial.print(bmp::altitude());
    Serial.println(" meters");

    Serial.print("Pressure at sealevel (calculated) = ");
    Serial.print(bmp::sealevel_pressure());
    Serial.println(" Pa");

    Serial.print("Real altitude = ");
    Serial.print(bmp::real_altitude());
    Serial.println(" meters");
    
    Serial.println();
    delay(500);
}	