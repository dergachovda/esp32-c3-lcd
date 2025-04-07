#include "Led.h"

Led::Led() : pin(-1), state(false), previousMillis(0), blinkInterval(0), isBlinking(false) {}

void Led::setPin(int pin) {
    this->pin = pin;
    pinMode(pin, OUTPUT);
    off(); // Ensure the LED is off initially
}

void Led::on() {
    isBlinking = false;
    state = true;
    digitalWrite(pin, isLogicInverted ? LOW : HIGH);
}

void Led::off() {
    isBlinking = false;
    state = false;
    digitalWrite(pin, isLogicInverted ? HIGH : LOW);
}

void Led::blink(unsigned long interval) {
    isBlinking = true;
    blinkInterval = interval;
}

void Led::loop() {
    if (isBlinking) {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= blinkInterval) {
            previousMillis = currentMillis;
            if (state) {
                off(); // Turn off the LED
            } else {
                on(); // Turn on the LED
            }
        }
    }
}

void Led::setInvertedLogic(bool inverted) {
    isLogicInverted = inverted;
}