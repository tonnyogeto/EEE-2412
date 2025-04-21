#include "servoControl.h"

Servo myServo;  // Define the Servo object

// Function to move the servo to a specific angle
void moveServo(int angle) {
  myServo.write(angle);
}
