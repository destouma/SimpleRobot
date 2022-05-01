#include "Robot.hpp"
#include "Arduino.h"

Robot::Robot(){
  servoLeft.attach(servoLeftPin); 
  servoRight.attach(servoRightPin); 
}

void Robot::stopMove(int timeMs){
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  delay(timeMs);
}

void Robot::moveForward(int timeMs){
  servoLeft.writeMicroseconds(1600);
  servoRight.writeMicroseconds(1400);
  delay(timeMs);
}
    
void Robot::moveBackward(int timeMs){
  servoLeft.writeMicroseconds(1400);
  servoRight.writeMicroseconds(1600);
  delay(timeMs);
}

void Robot::turnLeft(int timeMs){
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1400);
  delay(timeMs);
}

void Robot::turnRight(int timeMs){
  servoLeft.writeMicroseconds(1600);
  servoRight.writeMicroseconds(1500);
  delay(timeMs);
}
