#include <Arduino.h>
#include "motors.h"

#ifndef Ultrasonic_h
#define Ultrasonic_h

// Set the collision distance
#define collision_distance 50

/* ----------------------------------------------------
    Define PINs for Elegoo SmartCar Shield v1.1
------------------------------------------------------*/

// 2 - UltraSonic: GND, 5V, Pin12, Pin13
#define pin_us_trig 13
#define pin_us_echo 12

/* ----------------------------------------------------
    Function prototypes
------------------------------------------------------*/
void setupservo();
int read_distance_Ultrasonic();
bool checkDirection(enum MotionControlDirections direction);
MotionControlDirections clearDirection();

#endif