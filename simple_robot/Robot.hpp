#pragma once
#include <Servo.h> 

class Robot{
private:
    Servo servoLeft;
    Servo servoRight;
    int servoLeftPin = 3;
    int servoRightPin = 4; 
public:
    Robot();
    void stopMove(int timeMs);
    void moveForward(int timeMs);
    void moveBackward(int timeMs);
    void turnLeft(int timeMs);
    void turnRight(int timeMs);
};
