#include "RobotServer.hpp"
#include "Robot.hpp"
#include <Arduino.h>
#include <WiFiNINA.h>
#include "WifiSecret.h"


void RobotServer::initServer(){
  Serial.println("initServer");
  enableWiFi();
  connectWiFi();
  server.begin();
  printWifiStatus();
  robot.stopMove(1000);
}


void RobotServer::runServer(){
  client = server.available();

  if (client) {
    printWeb();
  }
}

void RobotServer::enableWiFi() {
  Serial.println("enableWiFi");
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < "1.0.0") {
    Serial.println("Please upgrade the firmware");
  }
}

void RobotServer::connectWiFi() {
  Serial.println("connectWiFi");
  while (status != WL_CONNECTED) {
    Serial.println("connectWiFi try to connect");
    status = WiFi.begin(SECRET_SSID,SECRET_PASS);
    delay(10000);
  }
}

void RobotServer::printWifiStatus() {
  Serial.println("printWifiStatus");
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");

  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}


void RobotServer::printWeb() {
   if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {

            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
           
            //create the buttons
            client.print("Click <a href=\"/F\">here</a> move forward <br>");
            client.print("Click <a href=\"/B\">here</a> move backward <br>");
            client.print("Click <a href=\"/L\">here</a> turn left <br>");
            client.print("Click <a href=\"/R\">here</a> turn right <br>");
           
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }
          else {      // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        if (currentLine.endsWith("GET /F")) {
            robot.moveForward(500);
            robot.stopMove(1);
        }
        if (currentLine.endsWith("GET /B")) {
          robot.moveBackward(500);
          robot.stopMove(1);
        }
        if (currentLine.endsWith("GET /L")) {
          robot.turnLeft(500);
          robot.stopMove(1);    
        }
        if (currentLine.endsWith("GET /R")) {
          robot.turnRight(500);
          robot.stopMove(1);      
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}
  
