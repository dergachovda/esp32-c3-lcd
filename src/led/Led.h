#ifndef LED_H
#define LED_H

#include <Arduino.h>

class Led {
private:
    int pin;
    bool state;
    unsigned long previousMillis;
    unsigned long blinkInterval;
    bool isBlinking;

public:
    Led();
    void setPin(int pin);
    void on();
    void off();
    void blink(unsigned long interval);
    void loop();
};

#endif // LED_H