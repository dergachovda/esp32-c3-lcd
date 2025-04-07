#include "XboxControllerClient.h"
#include <Arduino.h>

XboxControllerClient::XboxControllerClient() : xboxController() {}
XboxControllerClient::XboxControllerClient(String macAddress) : xboxController(macAddress) {}

void XboxControllerClient::begin() {
    xboxController.begin();
    Serial.println("Xbox Controller Client initialized.");
}

void XboxControllerClient::onLoop() {
    xboxController.onLoop();
}

bool XboxControllerClient::isConnected() {
    // Check if the controller is connected
    if (xboxController.isConnected()) {
        // Check if the controller is waiting for the first notification
        if (xboxController.isWaitingForFirstNotification()) {
            Serial.println("Waiting for first notification...");
        } else {
            return true;
        }
    } else {
        Serial.println("Controller not connected.");
        if (xboxController.getCountFailedConnection() > 2) {
            ESP.restart();
        }
    }
    return false;
}

String XboxControllerClient::getDeviceAddress() {
    return xboxController.buildDeviceAddressStr();
}

void XboxControllerClient::printState() {
    Serial.println("Controller State:\n" + getState());
}

String XboxControllerClient::getState() {
    String output = "";
    if (isConnected()) {
        output += "Address: " + xboxController.buildDeviceAddressStr() + "\n";
        output += xboxController.xboxNotif.toString() + "\n";
        unsigned long receivedAt = xboxController.getReceiveNotificationAt();
        uint16_t joystickMax = XboxControllerNotificationParser::maxJoy;
        output += "joyLHori rate: " + String((float)xboxController.xboxNotif.joyLHori / joystickMax) + "\n";
        output += "joyLVert rate: " + String((float)xboxController.xboxNotif.joyLVert / joystickMax) + "\n";
        output += "battery " + String(xboxController.battery) + "%\n";
        output += "received at " + String(receivedAt) + "\n";
    } else {
        output += "not connected";
    }
    return output;
}

bool XboxControllerClient::getButtonStatus(Button button) {
    switch (button) {
        case BUTTON_A:
            return xboxController.xboxNotif.btnA;
        case BUTTON_B:
            return xboxController.xboxNotif.btnB;
        case BUTTON_X:
            return xboxController.xboxNotif.btnX;
        case BUTTON_Y:
            return xboxController.xboxNotif.btnY;
        case BUTTON_LB:
            return xboxController.xboxNotif.btnLB;
        case BUTTON_RB:
            return xboxController.xboxNotif.btnRB;
        default:
            return false; // Invalid button
    }
}
