#include "RobotServer.hpp"
 
RobotServer robotServer;
 
void setup() 
{ 
  Serial.begin(9600);
  while (! Serial);
  robotServer.initServer();
} 
 
void loop() 
{ 
  robotServer.runServer();
}
