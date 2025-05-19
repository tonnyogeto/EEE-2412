#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>
#define EN1 6
#define IN1 9
#define IN2 10

void motorSetup();
void moveForward(int speed);
void moveBackward(int speed);
void stopMotor();

#endif