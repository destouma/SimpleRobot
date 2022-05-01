#include "Robot.hpp"
#include <Arduino.h>
#include <WiFiNINA.h>

class RobotServer{
  private:
    Robot robot;
    WiFiServer server;
    WiFiClient client;
    int keyIndex = 0;                 
    int status = WL_IDLE_STATUS;
    void enableWiFi();
    void connectWiFi();
    void printWifiStatus();
    void printWeb();
  public:
    RobotServer() : server(80), robot() {};
    void initServer();
    void runServer();
};
