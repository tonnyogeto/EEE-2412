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

    digitalWrite(COL1, LOW);
    if (!digitalRead(ROW1)) key = '1';
    digitalWrite(COL1, HIGH);

    digitalWrite(COL2, LOW);
    if (!digitalRead(ROW1)) key = '2';
    if (!digitalRead(ROW4)) key = '0';
    digitalWrite(COL2, HIGH);

    return key;
}
