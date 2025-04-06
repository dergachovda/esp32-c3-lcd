
#ifndef XBOX_CONTROLLER_CLIENT_H
#define XBOX_CONTROLLER_CLIENT_H

#include <XboxSeriesXControllerESP32_asukiaaa.hpp>

class XboxControllerClient {
public:
    XboxControllerClient();
    XboxControllerClient(String macAddress);
    void begin();
    void update();
    bool isConnected();
    String getDeviceAddress();

private:
    // Xbox controller instance
    XboxSeriesXControllerESP32_asukiaaa::Core xboxController;
};

#endif // XBOX_CONTROLLER_CLIENT_H