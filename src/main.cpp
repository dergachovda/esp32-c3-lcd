#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

#define LED_PIN 8          // Internal LED pin (inverted)
#define BOOT_BUTTON_PIN 9  // BOOT button pin

// Initialize U8g2 for the OLED display (I2C pins 6 and 5)
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, 6, 5);

int width = 72;    // Width of the screen
int height = 40;   // Height of the screen
int xOffset = 30;  // Horizontal offset for centering the display
int yOffset = 12;  // Vertical offset for centering the display

bool ledState = false;               // Tracks the state of the LED (on/off)
bool buttonState = HIGH;             // Tracks the current state of the button
bool lastButtonState = HIGH;         // Tracks the previous state of the button
unsigned long lastDebounceTime = 0;  // Debounce timer
unsigned long debounceDelay = 50;    // Debounce delay (in milliseconds)
int pressCount = 0;                  // Track the number of button presses

void updateDisplay();
void displayText(const char *text);
void displayPressBtn();

void setup() {
    // Initialize digital pin LED_PIN as an output
    pinMode(LED_PIN, OUTPUT);

    // Initialize BOOT button pin as input with internal pull-up
    pinMode(BOOT_BUTTON_PIN, INPUT_PULLUP);

    // Start serial communication for logging
    Serial.begin(115200);
    Serial.println("Setup Complete.");

    // Initialize the OLED display
    u8g2.begin();
    u8g2.setContrast(255);        // Set contrast to maximum
    u8g2.setBusClock(400000);     // Set I2C bus clock to 400kHz
    digitalWrite(LED_PIN, HIGH);  // HIGH means LED is off due to inverted logic
    displayText("        Hi!");   // Display initial message
    delay(1000);                  // Delay for 1 second
    displayPressBtn();            // Display "Press btn..." message
}

void loop() {
    // Read the current state of the button (LOW when pressed)
    int reading = digitalRead(BOOT_BUTTON_PIN);

    // Check if the button state has changed (i.e., was pressed or released)
    if (reading != lastButtonState) {
        // Reset the debounce timer
        lastDebounceTime = millis();
    }

    // If the time since the last button state change is greater than the
    // debounce delay
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
            digitalWrite(
                LED_PIN,
                ledState ? LOW
                         : HIGH);  // LOW turns the LED on, HIGH turns it off

            // Log the LED state
            Serial.print("LED is now ");
            Serial.println(ledState ? "ON" : "OFF");

            // Update the OLED display with the new press count and LED state
            updateDisplay();
        }

        // Update the button state
        buttonState = reading;
    }

    // Save the current button state as the last state for the next loop
    // iteration
    lastButtonState = reading;
}

void displayText(const char *text) {
    u8g2.clearBuffer();                  // Clear the internal buffer
    u8g2.setFont(u8g2_font_ncenB08_tr);  // Set font

    // Draw a frame around the display area
    u8g2.drawFrame(xOffset, yOffset, width,
                   height);  // Draw frame

    // Display the text
    // print the text in a middle of the screen and scroll it
    u8g2.setCursor(xOffset + 2, yOffset + 25);  // Set position for text
    u8g2.print(text);                           // Print text

    u8g2.sendBuffer();  // Transfer internal memory to the display
}

void displayPressBtn() {
    u8g2.clearBuffer();                  // Clear the internal buffer
    u8g2.setFont(u8g2_font_ncenB08_tr);  // Set font

    // Draw a frame around the display area
    u8g2.drawFrame(xOffset, yOffset, width,
                   height);  // Draw frame

    u8g2.drawTriangle(xOffset + width - 10, yOffset + 5, xOffset + width - 5,
                      yOffset + 2, xOffset + width - 3, yOffset + 8);
    // droaw a line to represent the button
    u8g2.drawLine(
        xOffset + width - 5, yOffset + 2,
        xOffset + width - 12,  yOffset + 12);

    // Display the text
    // print the text in a middle of the screen and scroll it
    u8g2.setCursor(xOffset + 2, yOffset + 25);  // Set position for text
    u8g2.print("  Press btn...");               // Print text

    u8g2.sendBuffer();  // Transfer internal memory to the display
}

void updateDisplay() {
    u8g2.clearBuffer();                  // Clear the internal buffer
    u8g2.setFont(u8g2_font_ncenB08_tr);  // Set font

    // Draw a frame around the display area
    u8g2.drawFrame(xOffset, yOffset, width, height);  // Draw frame

    // Display the press count
    u8g2.setCursor(xOffset + 2, yOffset + 11);  // Set position for text
    u8g2.print("Press Count:");

    u8g2.setCursor(xOffset + 2, yOffset + 23);  // Set position for text
    u8g2.printf("      %d", pressCount);
    // Display the LED state
    u8g2.setCursor(xOffset + 2, yOffset + 36);  // Set position for LED state
    u8g2.printf("LED is %s", ledState ? "ON" : "OFF");  // Print LED state

    u8g2.sendBuffer();  // Transfer internal memory to the display
}
