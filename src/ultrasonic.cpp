#include "ultrasonic.h"
#include "motors.h"
#include "Arduino.h"

/* ----------------------------------------------------
    Variable Declarations
------------------------------------------------------*/
// 2 - UltraSonic: GND, 5V, Pin12, Pin13
#define collision_distance 50
float distance, duration;

// Create a servo head object
Servo servo_head;

/* ----------------------------------------------------
    Function: setup_servo
    Description: Attach servo for UltraSonic
    Input: none
    Return: none
------------------------------------------------------*/
void setup_servo()
{
  servo_head.attach(pin_servo_head);    // 1 - Servo for UltraSonic 
}

/* ----------------------------------------------------
    Function: distance_UltraSonic
    Description: Read UltraSonic and return distance
    Input: none
    Return: Current distance read by ultrasonic sensor
------------------------------------------------------*/
int read_distance_Ultrasonic()
{
  // Set trig pin low to reset
  digitalWrite(pin_us_trig, LOW);
  delay(2);

  // Write trig pin low to transmit
  digitalWrite(pin_us_trig, HIGH);
  delay(10);
  digitalWrite(pin_us_trig, LOW);

  // Calculate the distance based on the time
  duration = pulseIn(pin_us_echo, HIGH);
  distance = (duration*.0343)/2;

  // Return the distance currently read
  return distance;
}

/* ----------------------------------------------------
    Function: checkDirection
    Description: Check if a specified direction is clear
    Input: Direction to check
    Return: Direction clear status as bool
------------------------------------------------------*/
bool checkDirection(MotionControlDirections direction)
{
  // Check a specified direction
  servoHeadMove(direction);
  int sensor_distance = read_distance_Ultrasonic();
  delay(100);

  // Read distance and return if close
  if (sensor_distance > collision_distance)
  {
    return true;
  }
  return false;
}

/* ----------------------------------------------------
    Function: MotionControlDirections
    Description: Check which direction is clear
    Input: none
    Return: Clear direction where no object exists
------------------------------------------------------*/
MotionControlDirections clearDirection()
{ 
  // Initialize - nothing clear
  bool clear_left = false;
  bool clear_forward = false;
  bool clear_right = false;
  delay(100);

  // Check left and right
  clear_left = checkDirection(Left);
  delay(1000);
  clear_right = checkDirection(Right);
  delay(1000);

  // Reset head to point forward
  servoHeadMove(Forward);
  clear_forward = checkDirection(Forward);

    // Handle direction change, default turn to the left
    if (clear_forward && clear_right && clear_left) {
        return Forward;
    }
    else if (clear_left) {
        return Left;
    }
    else if (clear_right) {
        return Right;
    }
    else {
        return Backwards;
    }

}