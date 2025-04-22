#include <Arduino.h>
#include "keypad/keypadHandler.h"
#include "motor/motorControl.h"
#include "ultrasonic/ultrasonicSensor.h"
#include "buttons/buttonPins.h"



// Enums for floor and direction
enum Floor { GROUND = 0, MIDDLE = 1, TOP = 2 };
enum Direction { IDLE, UP, DOWN };

// Global state variables
Floor currentFloor = GROUND;
Direction liftDirection = IDLE;
bool isMoving = false;

void moveToFloor(Floor target) {
    if (target == currentFloor) return;

    liftDirection = (target > currentFloor) ? UP : DOWN;

    if (liftDirection == UP) {
        moveForward(150);
    } else {
        moveBackward(150);
    }

    delay(3000);  // Simulate travel time (you can replace with ultrasonic logic)
    stopMotor();

    currentFloor = target;
    liftDirection = IDLE;
    isMoving = false;
}

void setup() {
    Serial.begin(9600);
    keypadSetup();
    motorSetup();
    ultrasonicSetup();

    pinMode(BTN_GND_UP, INPUT_PULLUP);
    pinMode(BTN_MID_UP, INPUT_PULLUP);
    pinMode(BTN_MID_DOWN, INPUT_PULLUP);
    pinMode(BTN_TOP_DOWN, INPUT_PULLUP);
}

void loop() {
    bool callFromGround = IS_PRESSED(BTN_GND_UP);
    bool callFromMiddleUp = IS_PRESSED(BTN_MID_UP);
    bool callFromMiddleDown = IS_PRESSED(BTN_MID_DOWN);
    bool callFromTop = IS_PRESSED(BTN_TOP_DOWN);

    if (!isMoving) {
        if (callFromGround && currentFloor == GROUND) {
            moveToFloor(MIDDLE);  // default priority upward from ground
        } else if (callFromMiddleUp && currentFloor == MIDDLE) {
            moveToFloor(TOP);
        } else if (callFromMiddleDown && currentFloor == MIDDLE) {
            moveToFloor(GROUND);
        } else if (callFromTop && currentFloor == TOP) {
            moveToFloor(MIDDLE);
        }
        // Prioritize calls while the lift is idle
        else if (callFromGround) {
            moveToFloor(MIDDLE);
        } else if (callFromMiddleUp) {
            moveToFloor(TOP);
        } else if (callFromTop) {
            moveToFloor(MIDDLE);
        } else if (callFromMiddleDown) {
            moveToFloor(GROUND);
        }
    }

    // Handle keypad inputs only when lift is idle (inside cabin)
    char key = getKeypadInput();
    if (key && !isMoving) {
        if (key == '0') moveToFloor(GROUND);
        else if (key == '1') moveToFloor(MIDDLE);
        else if (key == '2') moveToFloor(TOP);
    }

    delay(100);
}
