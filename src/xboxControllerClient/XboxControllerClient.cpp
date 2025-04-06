#include "XboxControllerClient.h"
#include <Arduino.h>

XboxControllerClient::XboxControllerClient() : xboxController() {}
XboxControllerClient::XboxControllerClient(String macAddress) : xboxController(macAddress) {}

void XboxControllerClient::begin() {
    xboxController.begin();
    Serial.println("Xbox Controller Client initialized.");
}

void XboxControllerClient::update() {
    xboxController.onLoop();

    if (xboxController.isConnected()) {
        if (xboxController.isWaitingForFirstNotification()) {
            Serial.println("waiting for first notification");
        } else {
            Serial.println("Address: " +
                           xboxController.buildDeviceAddressStr());
            Serial.print(xboxController.xboxNotif.toString());
            unsigned long receivedAt =
                xboxController.getReceiveNotificationAt();
            uint16_t joystickMax = XboxControllerNotificationParser::maxJoy;
            Serial.print("joyLHori rate: ");
            Serial.println((float)xboxController.xboxNotif.joyLHori /
                           joystickMax);
            Serial.print("joyLVert rate: ");
            Serial.println((float)xboxController.xboxNotif.joyLVert /
                           joystickMax);
            Serial.println("battery " + String(xboxController.battery) + "%");
            Serial.println("received at " + String(receivedAt));
        }
  } else {
    Serial.println("not connected");
    if (xboxController.getCountFailedConnection() > 2) {
      ESP.restart();
    }
  }
}

bool XboxControllerClient::isConnected() {
    return xboxController.isConnected();
}

String XboxControllerClient::getDeviceAddress() {
    return xboxController.buildDeviceAddressStr();
}
