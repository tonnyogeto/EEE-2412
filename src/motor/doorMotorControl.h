#ifndef DOOR_MOTOR_CONTROL_H
#define DOOR_MOTOR_CONTROL_H

#include <Arduino.h>

#define DOOR_EN   5
#define DOOR_IN1  8
#define DOOR_IN2  13

void doorMotorSetup();
void openDoor();
void closeDoor();
void stopDoor();

#endif