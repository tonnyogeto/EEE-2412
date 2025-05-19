#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include <Arduino.h>
#define TRIG_PIN 12
#define ECHO_PIN 11

void ultrasonicSetup();
float getDistance();

#endif

