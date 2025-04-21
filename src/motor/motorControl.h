#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>  

// Define motor control pins
#define EN1 5   // PWM pin for speed control
#define IN1 9   // Direction control pin 1
#define IN2 10  // Direction control pin 2

// Function prototypes
void motorSetup();
void moveForward(int speed);
void moveBackward(int speed);
void stopMotor();

#endif  // MOTORCONTROL_H


