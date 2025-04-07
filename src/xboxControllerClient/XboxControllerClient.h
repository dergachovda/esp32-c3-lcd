
#ifndef XBOX_CONTROLLER_CLIENT_H
#define XBOX_CONTROLLER_CLIENT_H

#include <XboxSeriesXControllerESP32_asukiaaa.hpp>

class XboxControllerClient {
public:
    XboxControllerClient();
    XboxControllerClient(String macAddress);
    void begin();
    void onLoop();
    bool isConnected();
    String getDeviceAddress();
    void printState(); // Print the state of the controller
    String getState(); // Get the state of the controller as a string

    // Enum for Xbox Series controller buttons
    enum Button {
        BUTTON_A,
        BUTTON_B,
        BUTTON_X,
        BUTTON_Y,
        BUTTON_LB, // Left Bumper
        BUTTON_RB // Right Bumper
        // TBD: Add more buttons as needed
    };
    // Method to retrieve the status of a specific button
    bool getButtonStatus(Button button);

private:
    // Xbox controller instance
    XboxSeriesXControllerESP32_asukiaaa::Core xboxController;
};

#endif // XBOX_CONTROLLER_CLIENT_H