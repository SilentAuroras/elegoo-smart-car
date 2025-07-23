#include <Arduino.h>
#include "motors.h"
#include "ultrasonic.h"

// #define DEBUG    // Enable debugging and don't move motors

/* ----------------------------------------------------
    Function: Setup
    Description: Default Setup and Pin Initialization
    Input: none
    Return: none
------------------------------------------------------*/
void setup()
{
    // Initialize Pins
    pinMode(pin_servo_head, OUTPUT);           // 1 - Servo for UltraSonic
    pinMode(pin_us_trig, OUTPUT);              // 2 - UltraSonic
    pinMode(pin_us_echo, INPUT);               // 2 - UltraSonic
    pinMode(pin_enable_motor_control, OUTPUT); // 4 - Motor control chip
    pinMode(pin_motor_ain2_pwm, OUTPUT);       // 4 - Motors left bank pwm
    pinMode(pin_motor_ain, OUTPUT);            // 4 - Motors left bank
    pinMode(pin_motor_bin2_pwm, OUTPUT);       // 4 - Motors right bank pwm
    pinMode(pin_motor_bin, OUTPUT);            // 4 - Motors right bank

    // Enable motor control chip
    digitalWrite(pin_enable_motor_control, HIGH);

    // Enable servo for ultrasonic sensor
    setup_servo();

    // Pause when start up
    delay(2000);
}

/* ----------------------------------------------------
    Function: Loop
    Description: Main while loop
    Input: none
    Return: none
------------------------------------------------------*/
void loop()
{
    // Check current distance in front of Ultrasonic sensor
    float current_distance = read_distance_Ultrasonic();

    // Detect object directly in front
    if (current_distance <= collision_distance)
    {
        // Object detected, send stop action
        MoveMotors(Stop);

        // Check clear direction
        MotionControlDirections clear_direction = clearDirection();

        // Move clear direction
        MoveMotors(clear_direction);
    }
    else
    {
        // No object detected, keep moving forward
        MoveMotors(Forward);
    }
    delay(100);
}
