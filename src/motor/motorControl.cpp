#include "motorControl.h"

int motorSpeed = 100;

void motorSetup() {
    pinMode(EN1, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    stopMotor();
    Serial.println("Motor setup complete.");
}

void moveForward(int speed) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(EN1, constrain(speed, 0, 255));
    Serial.println("Motor moving FORWARD (DOWN)");
}

void moveBackward(int speed) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(EN1, constrain(speed, 0, 255));
    Serial.println("Motor moving BACKWARD (UP)");
}

void stopMotor() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(EN1, 0);
    Serial.println("Motor stopped.");
}