
//LDR Pin
#define LDR_PIN A0

// LDR Characteristics
const float GAMMA = 0.7;
const float RL10 = 50;

namespace data {
  namespace calculation {
    // Declaration of the Variables
    int analogValue;

    void readLDR(){
      analogValue = analogRead(LDR_PIN);
    }

    float voltage(){
      readLDR();
      return analogValue / 1024. * 5;
    }

    float resistance(){
      return 2000 * voltage() / (1 - voltage() / 5);
    }

    float lux(){
      return pow(RL10 * 1e3 * pow(10, GAMMA) / resistance(), (1 / GAMMA));
    }
  }
}

namespace ldr = data::calculation;

void ldr_test(){
  //ldr::readLDR();
  ldr::voltage();
  ldr::resistance();
  float lux_value = ldr::lux(); // Call the function and store the result
  Serial.print("Lux: ");
  Serial.println(lux_value); // Print the result
  delay(1000);
}

void serialLDR(){
  Serial.print("Voltage: ");
  Serial.print(ldr::voltage());
  Serial.println(" V");

  Serial.print("Resistance: ");
  Serial.print(ldr::resistance());
  Serial.println(" Ohm");

  Serial.print("Lux: ");
  Serial.print(ldr::lux());
  Serial.println(" lux");

  delay(500);
}