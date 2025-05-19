#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "lcd.h"

// Change the I2C address (usually 0x27 or 0x3F depending on your module)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void lcdSetup() {
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Elevator Ready");
}

void displayFloor(const char* floor) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Current Floor:");
    lcd.setCursor(0, 1);
    lcd.print(floor);
}

