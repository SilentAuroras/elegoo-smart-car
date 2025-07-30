#pragma once

/* ----------------------------------------------------
    Define PINs for Elegoo SmartCar Shield v1.1
------------------------------------------------------*/
// 5 - Power Module: GND, 5V, PinA3
#define pin_battery A3

/* ----------------------------------------------------
    Function prototypes
------------------------------------------------------*/
float batteryVoltage();
void noPowerShake();