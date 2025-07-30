#include <Arduino.h>
#include "motors.h"
#include "power.h"
#include "ultrasonic.h"

float battery_voltage;
bool DEBUG = false;

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

    // Pull initial battery voltage to detect if just running on USB power for debugging
    battery_voltage = batteryVoltage();

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
    // Check if car is on battery power or USB power (5V), pulled in setup()
    constexpr float usb_threshold = 5.0;

    if (battery_voltage < usb_threshold) {
        // Just run shake once, voltage check does not work in setup()
        noPowerShake();     // Shake servo head if no power
        DEBUG = true;       // Plugged into USB power, set debug mode, don't move motors
    }

    // Check current distance in front of Ultrasonic sensor
    const float current_distance = read_distance_Ultrasonic();

    // Detect an object directly in front
    if (current_distance <= collision_distance)
    {
        // Object detected, send stop action
        MoveMotors(Stop);

        // Check a clear direction
        MotionControlDirections clear_direction = clearDirection();

        // Move in a clear direction
        MoveMotors(clear_direction);
    }
    else
    {
        // No object detected, keep moving forward
        MoveMotors(Forward);
    }
    delay(100);
}
