#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include <Arduino.h>

// Define Ultrasonic Sensor Pins
#define TRIG_PIN 12
#define ECHO_PIN 11

// Function prototypes
void ultrasonicSetup();    // <-- Add this line
float getDistance();

#endif
