#ifndef BUTTON_PINS_H
#define BUTTON_PINS_H

// External push button pin definitions
#define BTN_GND_UP     A0  // Ground floor: going up
#define BTN_MID_UP     A1  // Middle floor: going up
#define BTN_MID_DOWN   A2  // Middle floor: going down
#define BTN_TOP_DOWN   A3  // Top floor: going down

// Helper macro to simplify input logic
#define IS_PRESSED(pin) (!digitalRead(pin))

#endif  // BUTTON_PINS_H

