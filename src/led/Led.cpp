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
    digitalWrite(pin, LOW); // LOW turns the LED on (inverted logic)
}

void Led::off() {
    isBlinking = false;
    state = false;
    digitalWrite(pin, HIGH); // HIGH turns the LED off (inverted logic)
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
            state = !state;
            digitalWrite(pin, state ? LOW : HIGH); // Toggle LED state
        }
    }
}