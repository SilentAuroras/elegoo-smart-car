#include <Arduino.h>
#include <Servo.h>

#ifndef Motors_h
#define Motors_h

/* ----------------------------------------------------
    Define PINs for Elegoo SmartCar Shield v1.1
------------------------------------------------------*/
// 1 - Servo for UltraSonic: GND, 5V, Pin10
#define pin_servo_head 10
extern Servo servo_head;

// 4 - Motors: GND, 5V, Pin5, Pin6, Pin7, Pin8
#define pin_enable_motor_control 3 // turn on motor control
#define pin_motor_ain 8            // AIN - APHASE - Pin10
#define pin_motor_ain2_pwm 5       // AIN2 - AENBL - Pin9
#define pin_motor_bin 7            // BIN1 - BPHASE - Pin8
#define pin_motor_bin2_pwm 6       // BIN2 - BENBL - Pin7

/* ----------------------------------------------------
    Define Enum
------------------------------------------------------*/
// Enum for direction control
enum MotionControlDirections
{
    Forward = 0,
    Backward = 1,
    Left = 2,
    Right = 3,
    Stop = 4
};

/* ----------------------------------------------------
    Function prototypes
------------------------------------------------------*/
void servoHeadMove(enum MotionControlDirections check);
void MoveMotors(enum MotionControlDirections dir);

#endif
