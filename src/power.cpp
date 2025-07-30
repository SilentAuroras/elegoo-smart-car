#include "power.h"
#include <Arduino.h>
#include "motors.h"

/* ----------------------------------------------------
    Function: batteryVoltage
    Description: Check the battery voltage
    Input: none
    Return: battery voltage float
------------------------------------------------------*/
float batteryVoltage() {

    // Read the analog value from the battery pin
    const int powerValue = analogRead(pin_battery);
    constexpr float referenceVoltage = 5.0;
    constexpr int adcResolution = 1023;
    const float voltage = (powerValue * referenceVoltage) / adcResolution;

    // Voltage divider calculation
    constexpr float dividerRatio = (10000.0 + 1500.0) / 1500;
    const float battery_voltage = voltage * dividerRatio;

    return battery_voltage;
}

/* ----------------------------------------------------
    Function: noPowerShake
    Description: Shake servo head if no power
    Input: none
    Return: none
------------------------------------------------------*/
void noPowerShake() {
    for (int i = 0; i < 3; i++) {
        servoHeadMove(Left);
        delay(200);
        servoHeadMove(Right);
        delay(200);
    }
}