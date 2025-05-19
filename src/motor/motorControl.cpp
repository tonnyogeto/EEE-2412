#include "motorControl.h"

void motorSetup() {
    pinMode(EN1, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    stopMotor();
    Serial.println("Lift motor setup complete.");
}

void moveForward(int speed) {
    Serial.println("Motor: moveForward (UP)");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(EN1, speed);
}

void moveBackward(int speed) {
    Serial.println("Motor: moveBackward (DOWN)");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(EN1, speed);
}

void stopMotor() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(EN1, 0);
    Serial.println("Motor: STOP");
}
