#include "motorControl.h"

int motorSpeed = 15; // Default speed (adjustable from 0-255)

void motorSetup() {
    Serial.begin(9600);
    pinMode(EN1, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    Serial.println("Motor setup complete, stopping motor...");
    stopMotor();
}

void moveForward(int speed) {
    Serial.print("Motor Forward at speed: ");
    Serial.println(speed);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(EN1, speed);
}

void moveBackward(int speed) {
    Serial.print("Motor Backward at speed: ");
    Serial.println(speed);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(EN1, speed);
}

void stopMotor() {
    Serial.println("Motor Stopped");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(EN1, 0);
}
