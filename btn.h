#define left_button 10
#define select_button 9
#define right_button 8

const int buttons[3] = {left_button, select_button, right_button};

namespace button{
    unsigned long interval = 200;
    unsigned long buttonPressedTime = 0;
    bool buttonState = false;

    void start(){
        for(int i = 0; i < 3; i++)
            pinMode(buttons[i], INPUT_PULLUP);
    }

    bool read(int buttonPin){
        unsigned long currentMillis = millis();
        int reading = digitalRead(buttonPin);

        if(reading == LOW && !buttonState){
            // Button was just pressed
            buttonState = true;
            buttonPressedTime = currentMillis;
        }

        if(reading == HIGH && buttonState){
            // Button was just released
            buttonState = false;
            interval = 200;  // Reset the interval to 200ms
        }
        
        return buttonState;
    }

    bool left() {return read(left_button);}
    bool right() {return read(right_button);}
    bool select() {return read(select_button);}
    
    void debug(){
        Serial.print("Left: ");
        Serial.print(left());
        Serial.print(" | Select: ");
        Serial.print(select());
        Serial.print(" | Right: ");
        Serial.println(right());
    }
}