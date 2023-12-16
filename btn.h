#define left_button 10
#define select_button 9
#define right_button 8

namespace button{
    void start(){
        pinMode(left_button, INPUT_PULLUP);
        pinMode(right_button, INPUT_PULLUP);
        pinMode(select_button, INPUT_PULLUP);
    }

    bool left(){
        return digitalRead(right_button);
    }

    bool right(){
        return digitalRead(right_button);
    }

    bool select(){
        return digitalRead(select_button);
    }

    void debug(){
        Serial.print("Left: ");
        Serial.print(left());
        Serial.print(" | Right: ");
        Serial.print(right());
        Serial.print(" | Select: ");
        Serial.println(select());
    }
}