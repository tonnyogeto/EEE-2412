#include "keypadHandler.h"
#include <Arduino.h>

// Define keypad pins
#define ROW1 2  // Row for key '1' and '2'
#define ROW4 3  // Row for key '0'
#define COL1 4  // Column for key '1'
#define COL2 7  // Column for key '0' and '2'

void keypadSetup() {
    pinMode(ROW1, INPUT_PULLUP);
    pinMode(ROW4, INPUT_PULLUP);
    pinMode(COL1, OUTPUT);
    pinMode(COL2, OUTPUT);
}

// Function to check which key is pressed
char getKeypadInput() {
    digitalWrite(COL1, LOW);  // Activate Column 1
    if (!digitalRead(ROW1)) return '1';  // If Row 1 is LOW, key '1' is pressed

    digitalWrite(COL2, LOW);  // Activate Column 2
    if (!digitalRead(ROW1)) return '2';  // If Row 1 is LOW, key '2' is pressed
    if (!digitalRead(ROW4)) return '0';  // If Row 4 is LOW, key '0' is pressed

    return '\0';  // No key pressed
}
