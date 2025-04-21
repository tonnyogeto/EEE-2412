#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

#include <Arduino.h>
#include <Servo.h>

// Function prototype
void moveServo(int angle);

extern Servo myServo;  // Declare the Servo object globally

#endif
