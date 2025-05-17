#ifndef DOOR_MOTOR_CONTROL_H
#define DOOR_MOTOR_CONTROL_H

#include <Arduino.h>

#define DOOR_EN   5   // PWM speed control
#define DOOR_IN1  8   // Direction 1
#define DOOR_IN2  13   // Direction 2

void doorMotorSetup();
void openDoor();
void closeDoor();
void stopDoor();

#endif
