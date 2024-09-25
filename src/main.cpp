#include <Arduino.h>

#define LED_PIN 8         // Internal LED pin (inverted)
#define BOOT_BUTTON_PIN 9 // BOOT button pin

bool ledState = false;  // Tracks the state of the LED (on/off)
bool buttonState = HIGH;  // Tracks the current state of the button
bool lastButtonState = HIGH;  // Tracks the previous state of the button
unsigned long lastDebounceTime = 0;  // Debounce timer
unsigned long debounceDelay = 50;    // Debounce delay (in milliseconds)
int pressCount = 0;  // Track the number of button presses

void setup() {
  // Initialize digital pin LED_PIN as an output
  pinMode(LED_PIN, OUTPUT);

  // Initialize BOOT button pin as input with internal pull-up
  pinMode(BOOT_BUTTON_PIN, INPUT_PULLUP);

  // Start serial communication for logging
  Serial.begin(115200);
  Serial.println("Setup Complete.");

  // Start with the LED turned off
  digitalWrite(LED_PIN, HIGH);  // HIGH means LED is off due to inverted logic
}

void loop() {
  // Read the current state of the button (LOW when pressed)
  int reading = digitalRead(BOOT_BUTTON_PIN);

  // Check if the button state has changed (i.e., was pressed or released)
  if (reading != lastButtonState) {
    // Reset the debounce timer
    lastDebounceTime = millis();
  }

  // If the time since the last button state change is greater than the debounce delay
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If the button state has changed and it's now pressed (LOW)
    if (reading == LOW && buttonState == HIGH) {
      // Increment the press count
      pressCount++;

      // Log the button press count
      Serial.print("Button Pressed. Press Count: ");
      Serial.println(pressCount);

      // Toggle the LED state
      ledState = !ledState;

      // Update the LED
      digitalWrite(LED_PIN, ledState ? LOW : HIGH);  // LOW turns the LED on, HIGH turns it off

      // Log the LED state
      Serial.print("LED is now ");
      Serial.println(ledState ? "ON" : "OFF");
    }

    // Update the button state
    buttonState = reading;
  }

  // Save the current button state as the last state for the next loop iteration
  lastButtonState = reading;
}
