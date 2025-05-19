#include "keypadHandler.h"
#include <Arduino.h>

#define ROW1 2
#define ROW4 3
#define COL1 4
#define COL2 7

void keypadSetup() {
    pinMode(ROW1, INPUT_PULLUP);
    pinMode(ROW4, INPUT_PULLUP);
    pinMode(COL1, OUTPUT);
    pinMode(COL2, OUTPUT);

    digitalWrite(COL1, HIGH);
    digitalWrite(COL2, HIGH);
}

char getKeypadInput() {
    char key = '\0';

    // Scan COL1
    digitalWrite(COL1, LOW);
    digitalWrite(COL2, HIGH);
    delay(5);
    if (!digitalRead(ROW1)) key = '1';
    delay(5);
    digitalWrite(COL1, HIGH);

    // Scan COL2
    digitalWrite(COL2, LOW);
    digitalWrite(COL1, HIGH);
    delay(5);
    if (!digitalRead(ROW1)) key = '2';
    if (!digitalRead(ROW4)) key = '0';
    delay(5);
    digitalWrite(COL2, HIGH);

    // Debounce: wait until key is released
    if (key != '\0') {
        while (!digitalRead(ROW1) || !digitalRead(ROW4)) {
            delay(10);
        }
    }

    return key;
}