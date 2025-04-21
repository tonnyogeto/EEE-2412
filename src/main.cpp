#include <Arduino.h>
#include "keypad/keypadHandler.h"
#include "motor/motorControl.h"
#include "ultrasonic/ultrasonicSensor.h"
#include "buttons/buttonPins.h"



// Floor states
enum Floor {GROUND = 0, MIDDLE = 1, TOP = 2};
Floor currentFloor = GROUND;

// Lift direction
enum Direction {IDLE, UP, DOWN};
Direction liftDirection = IDLE;

void setup() {
    Serial.begin(9600);
    keypadSetup();
    motorSetup();
    ultrasonicSetup();

    // Configure button pins
    pinMode(BTN_GND_UP, INPUT_PULLUP);
    pinMode(BTN_MID_UP, INPUT_PULLUP);
    pinMode(BTN_MID_DOWN, INPUT_PULLUP);
    pinMode(BTN_TOP_DOWN, INPUT_PULLUP);
}

void loop() {
    // Read external button requests
    bool callFromGround = IS_PRESSED(BTN_GND_UP);
    bool callFromMiddleUp = IS_PRESSED(BTN_MID_UP);
    bool callFromMiddleDown = IS_PRESSED(BTN_MID_DOWN);
    bool callFromTop = IS_PRESSED(BTN_TOP_DOWN);

    // Handle floor requests based on current floor and direction
    if (liftDirection == IDLE) {
        if (currentFloor == GROUND && callFromGround) {
            // Prioritize middle before top
            if (callFromMiddleUp) moveToFloor(MIDDLE);
            else if (callFromTop) moveToFloor(TOP);
        }
        else if (currentFloor == MIDDLE) {
            if (callFromMiddleUp) moveToFloor(TOP);
            else if (callFromMiddleDown) moveToFloor(GROUND);
        }
        else if (currentFloor == TOP && callFromTop) {
            // Prioritize going to middle before ground
            if (callFromMiddleDown) moveToFloor(MIDDLE);
            else moveToFloor(GROUND);
        }
    }

    // Handle keypad input when cabin is idle
    if (liftDirection == IDLE) {
        char key = getKeypadInput();
        if (key == '0') moveToFloor(GROUND);
        else if (key == '1') moveToFloor(MIDDLE);
        else if (key == '2') moveToFloor(TOP);
    }

    delay(200); // Debounce
}

void moveToFloor(Floor target) {
    if (target == currentFloor) return;

    if (target > currentFloor) {
        liftDirection = UP;
        moveForward(15);
        Serial.println("Going up...");
    } else {
        liftDirection = DOWN;
        moveBackward(15);
        Serial.println("Going down...");
    }

    delay(3000); // Simulate motion delay (replace with getDistance() for real-world detection)
    stopMotor();

    currentFloor = target;
    liftDirection = IDLE;
    Serial.print("Reached floor: ");
    Serial.println(currentFloor);
}
