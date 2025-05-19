#include "doorMotorControl.h"

// Slower speed for door motor
#define DOOR_SPEED 100              // Adjust speed as needed (0–255)
#define DOOR_MOVE_DURATION 1000    // Duration to run motor in ms

void doorMotorSetup() {
    pinMode(DOOR_IN1, OUTPUT);
    pinMode(DOOR_IN2, OUTPUT);
    pinMode(DOOR_EN, OUTPUT);
    stopDoor();
}

void openDoor() {
    Serial.println("Opening door...");
    digitalWrite(DOOR_IN1, LOW);
    digitalWrite(DOOR_IN2, HIGH);
    analogWrite(DOOR_EN, DOOR_SPEED);
    delay(DOOR_MOVE_DURATION);
    stopDoor();
}

void closeDoor() {
    Serial.println("Closing door...");
    digitalWrite(DOOR_IN1, HIGH);
    digitalWrite(DOOR_IN2, LOW);
    analogWrite(DOOR_EN, DOOR_SPEED);
    delay(DOOR_MOVE_DURATION);
    stopDoor();
}

void stopDoor() {
    analogWrite(DOOR_EN, 0);
    digitalWrite(DOOR_IN1, LOW);
    digitalWrite(DOOR_IN2, LOW);
}

