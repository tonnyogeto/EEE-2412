#include "doorMotorControl.h"

void doorMotorSetup() {
    pinMode(DOOR_EN, OUTPUT);
    pinMode(DOOR_IN1, OUTPUT);
    pinMode(DOOR_IN2, OUTPUT);
    stopDoor();
    Serial.println("Door motor setup complete.");
}

void openDoor() {
    Serial.println("Opening door...");
    digitalWrite(DOOR_IN1, LOW);
    digitalWrite(DOOR_IN2, HIGH);
    analogWrite(DOOR_EN, 150);  // Adjust speed as needed
    delay(1000);  // Time to fully open
    stopDoor();
}

void closeDoor() {
    Serial.println("Closing door...");
    digitalWrite(DOOR_IN1, HIGH);
    digitalWrite(DOOR_IN2, LOW);
    analogWrite(DOOR_EN, 150);  // Adjust speed as needed
    delay(1000);  // Time to fully close
    stopDoor();
}

void stopDoor() {
    digitalWrite(DOOR_IN1, LOW);
    digitalWrite(DOOR_IN2, LOW);
    analogWrite(DOOR_EN, 0);
}
