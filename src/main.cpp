#include <Arduino.h>
#include "keypad/keypadHandler.h"
#include "motor/motorControl.h"
#include "ultrasonic/ultrasonicSensor.h"
#include "buttons/buttonPins.h"
#include "motor/doorMotorControl.h"  

// Enums for floor and direction
enum Floor { GROUND = 0, MIDDLE = 1, TOP = 2 };
enum Direction { IDLE, UP, DOWN };

// Global state variables
Direction liftDirection = IDLE;
bool isMoving = false;

// Target distances for each floor (in cm)
#define DIST_GROUND 45
#define DIST_MIDDLE 30
#define DIST_TOP    0
#define FLOOR_TOLERANCE 4

float getTargetDistance(Floor floor) {
    switch (floor) {
        case GROUND: return DIST_GROUND;
        case MIDDLE: return DIST_MIDDLE;
        case TOP:    return DIST_TOP;
        default: return DIST_GROUND;
    }
}

Floor getCurrentFloorFromSensor() {
    float distance = getDistance();
    if (abs(distance - DIST_GROUND) <= FLOOR_TOLERANCE) return GROUND;
    else if (abs(distance - DIST_MIDDLE) <= FLOOR_TOLERANCE) return MIDDLE;
    else return TOP;
}

void moveToFloor(Floor target) {
    Floor currentFloor = getCurrentFloorFromSensor();

    if (target == currentFloor) return;

    float targetDistance = getTargetDistance(target);
    float currentDistance = getDistance();

    liftDirection = (target > currentFloor) ? UP : DOWN;
    isMoving = true;

    Serial.print("Moving from floor ");
    Serial.print(currentFloor);
    Serial.print(" to ");
    Serial.println(target);

    if (currentDistance < targetDistance - FLOOR_TOLERANCE) {
        moveForward(100);  // DOWN
        while (getDistance() < targetDistance - FLOOR_TOLERANCE) {
            delay(100);
        }
    } else if (currentDistance > targetDistance + FLOOR_TOLERANCE) {
        moveBackward(100); // UP
        while (getDistance() > targetDistance + FLOOR_TOLERANCE) {
            delay(100);
        }
    }

    stopMotor();
    liftDirection = IDLE;
    isMoving = false;

    Serial.println("Arrived at desired floor.");

    // Door operation logic
    openDoor();      // Open door
    delay(2000);     // Wait 2 seconds
    closeDoor();     // Close door
}

void setup() {
    Serial.begin(9600);
    keypadSetup();
    motorSetup();
    ultrasonicSetup();
    doorMotorSetup();  // <-- NEW

    pinMode(BTN_GND_UP, INPUT_PULLUP);
    pinMode(BTN_MID_UP, INPUT_PULLUP);
    pinMode(BTN_MID_DOWN, INPUT_PULLUP);
    pinMode(BTN_TOP_DOWN, INPUT_PULLUP);

    Serial.println("Elevator system initialized.");
}

void loop() {
    Floor currentFloor = getCurrentFloorFromSensor();

    bool callFromGround = IS_PRESSED(BTN_GND_UP);
    bool callFromMiddleUp = IS_PRESSED(BTN_MID_UP);
    bool callFromMiddleDown = IS_PRESSED(BTN_MID_DOWN);
    bool callFromTop = IS_PRESSED(BTN_TOP_DOWN);

    Serial.print("Detected Floor: ");
    Serial.println(currentFloor);

    if (!isMoving) {
        if (callFromGround && currentFloor == GROUND) {
            moveToFloor(MIDDLE);
        } else if (callFromMiddleUp && currentFloor == MIDDLE) {
            moveToFloor(TOP);
        } else if (callFromMiddleDown && currentFloor == MIDDLE) {
            moveToFloor(GROUND);
        } else if (callFromTop && currentFloor == TOP) {
            moveToFloor(MIDDLE);
        }
        // Prioritize external calls from any floor
        else if (callFromGround) {
            moveToFloor(GROUND);
        } else if (callFromMiddleUp) {
            moveToFloor(TOP);
        } else if (callFromTop) {
            moveToFloor(MIDDLE);
        } else if (callFromMiddleDown) {
            moveToFloor(GROUND);
        }
    }

    // Handle keypad inputs (inside cabin)
    char key = getKeypadInput();
    if (key && !isMoving) {
        if (key == '0') moveToFloor(GROUND);
        else if (key == '1') moveToFloor(MIDDLE);
        else if (key == '2') moveToFloor(TOP);
    }

    delay(100);
}
