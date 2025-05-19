#include <Arduino.h>
#include "keypad/keypadHandler.h"
#include "motor/motorControl.h"
#include "ultrasonic/ultrasonicSensor.h"
#include "buttons/buttonPins.h"
#include "motor/doorMotorControl.h"
#include "lcd/lcd.h"  // Include LCD

// Enums for floor and direction
enum Floor { GROUND = 0, MIDDLE = 1, TOP = 2 };
enum Direction { IDLE, UP, DOWN };

// Global state variables
Direction liftDirection = IDLE;
bool isMoving = false;

// Target distances for each floor (in cm)
#define DIST_GROUND 36
#define DIST_MIDDLE 16
#define DIST_TOP    0.7
#define FLOOR_TOLERANCE 4

float getTargetDistance(Floor floor) {
    switch (floor) {
        case GROUND: return DIST_GROUND;
        case MIDDLE: return DIST_MIDDLE;
        case TOP:    return DIST_TOP;
        default:     return DIST_GROUND;
    }
}

Floor getCurrentFloorFromSensor() {
    float distance = getDistance();
    if (abs(distance - DIST_GROUND) <= FLOOR_TOLERANCE) return GROUND;
    else if (abs(distance - DIST_MIDDLE) <= FLOOR_TOLERANCE) return MIDDLE;
    else return TOP;
}

const char* getFloorName(Floor floor) {
    switch (floor) {
        case GROUND: return "GROUND";
        case MIDDLE: return "MIDDLE";
        case TOP:    return "TOP";
        default:     return "UNKNOWN";
    }
}

void moveToFloor(Floor target) {
    Floor currentFloor = getCurrentFloorFromSensor();

    if (target == currentFloor) {
        Serial.println("Already on target floor.");
        return;
    }

    float targetDistance = getTargetDistance(target);
    float currentDistance = getDistance();

    // Debug info
    Serial.print("Current floor: "); Serial.println(currentFloor);
    Serial.print("Target floor: "); Serial.println(target);
    Serial.print("Current distance: "); Serial.println(currentDistance);
    Serial.print("Target distance: "); Serial.println(targetDistance);

    isMoving = true;

    if (currentDistance > targetDistance + FLOOR_TOLERANCE) {
        // We're below the target → Move UP (reduce distance)
        liftDirection = UP;
        Serial.println("Moving UP");
        moveForward(120);  // Full speed
        while (getDistance() > targetDistance + FLOOR_TOLERANCE) {
            delay(100);
        }
    } else if (currentDistance < targetDistance - FLOOR_TOLERANCE) {
        // We're above the target → Move DOWN (increase distance)
        liftDirection = DOWN;
        Serial.println("Moving DOWN");
        moveBackward(120);  // Full speed
        while (getDistance() < targetDistance - FLOOR_TOLERANCE) {
            delay(100);
        }
    }

    stopMotor();
    liftDirection = IDLE;
    isMoving = false;

    Serial.println("Arrived at desired floor.");

    delay(1000);  // Delay before opening the door

    openDoor();
    delay(2000);  // Keep door open
    closeDoor();
}

void setup() {
    Serial.begin(9600);
    keypadSetup();
    motorSetup();
    ultrasonicSetup();
    doorMotorSetup();
    lcdSetup();  // LCD initialization

    pinMode(BTN_GND_UP, INPUT_PULLUP);
    pinMode(BTN_MID_UP, INPUT_PULLUP);
    pinMode(BTN_MID_DOWN, INPUT_PULLUP);
    pinMode(BTN_TOP_DOWN, INPUT_PULLUP);

    Serial.println("Elevator system initialized.");
    displayFloor("Initializing...");
}

void loop() {
    Floor currentFloor = getCurrentFloorFromSensor();

    // Display current floor on LCD
    displayFloor(getFloorName(currentFloor));

    bool callFromGround = IS_PRESSED(BTN_GND_UP);
    bool callFromMiddleUp = IS_PRESSED(BTN_MID_UP);
    bool callFromMiddleDown = IS_PRESSED(BTN_MID_DOWN);
    bool callFromTop = IS_PRESSED(BTN_TOP_DOWN);

    Serial.print("Detected Floor: ");
    Serial.println(currentFloor);

    if (!isMoving) {
        // Handle calls from current floor
        if (callFromGround && currentFloor == GROUND) {
            moveToFloor(MIDDLE);
        } else if (callFromMiddleUp && currentFloor == MIDDLE) {
            moveToFloor(TOP);
        } else if (callFromMiddleDown && currentFloor == MIDDLE) {
            moveToFloor(GROUND);
        } else if (callFromTop && currentFloor == TOP) {
            moveToFloor(MIDDLE);
        }

        // Prioritize external calls
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

    // Handle keypad inputs
    char key = getKeypadInput();
    if (key && !isMoving) {
        Serial.print("Key pressed: ");
        Serial.println(key);
        if (key == '0') moveToFloor(GROUND);
        else if (key == '1') moveToFloor(MIDDLE);
        else if (key == '2') moveToFloor(TOP);
    }

    delay(100);
}
