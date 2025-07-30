#include "motors.h"
#include "Arduino.h"

/* ----------------------------------------------------
    Variable Declarations
------------------------------------------------------*/

// Debug flag
extern bool DEBUG;

// 1 - Servo for UltraSonic: GND, 5V, Pin10
short pos = 0;

// 4 - Motors: GND, 5V, Pin5, Pin6, Pin7, Pin8
#define motor_max_speed 125
#define LEFT_OFFSET 0.85 // Drifts to the right if not offset

// Setup timers for turn
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period_90_deg = 1000;

// Create enum for action to take
MotionControlDirections clear_direction;

/* ----------------------------------------------------
    Function: servoHeadMove
    Description: Move servo head for US based on degrees
    Input: Direction to move
    Return: None
------------------------------------------------------*/
void servoHeadMove(enum MotionControlDirections check)
{
  // Check left: 90->180
  if (check == Left)
  {
    for (int position = 90; position <= 180; position+=5)
      {
        servo_head.write(position);
        delay(15);
      }
  }
  // Check right: 90->0
  else if (check == Right)
  {
    for (int position = 90; position >= 0; position-=5)
      {
        servo_head.write(position);
        delay(15);
      }
  }
  // Forward: x->90
  else if (check == Forward)
  {
    servo_head.write(90);
  }
}

/* ----------------------------------------------------
    Function: MoveMotors
    Description: Move motors based on decided input
    Input: Direction to move
    Return: None
------------------------------------------------------*/
void MoveMotors(enum MotionControlDirections dir)
{
  // Update the start timer for turn duration
  startMillis = millis();
  currentMillis = millis();

  if (!DEBUG) {
    // Switch based on direction
    switch (dir) {
      case Forward:
      {
        // Left Bank
        digitalWrite(pin_motor_bin, HIGH);
        analogWrite(pin_motor_bin2_pwm, motor_max_speed*LEFT_OFFSET);

        // Right Bank
        digitalWrite(pin_motor_ain, HIGH);
        analogWrite(pin_motor_ain2_pwm, motor_max_speed);
        break;
      }
      case Backwards:
      {
        // Stop, turn left 90 degrees, then stop again before moving forward
        // Recursive call, but seems to work
        MoveMotors(Stop);
        MoveMotors(Left);
        MoveMotors(Left);
        MoveMotors(Stop);
        break;
      }
      case Left:
      {
        // Turn for x seconds
        while (true)
        {
          // Left Bank
          digitalWrite(pin_motor_bin, HIGH);
          analogWrite(pin_motor_bin2_pwm, motor_max_speed/2);

          // Right bank
          digitalWrite(pin_motor_ain, LOW);
          analogWrite(pin_motor_ain2_pwm, motor_max_speed/2);

          // When timer runs out, stop motors and exit
          if ((currentMillis - startMillis >= period_90_deg) && currentMillis != startMillis)
          {
            MoveMotors(Stop);
            break;
          }
          // Save currentMillis for the next loop
          currentMillis = millis();
        }
        break;
      }
      case Right:
      {
        // Turn for x seconds
        while (true)
        {
          // Left Bank
          digitalWrite(pin_motor_bin, LOW);
          analogWrite(pin_motor_bin2_pwm, motor_max_speed/2);

          // Right bank
          digitalWrite(pin_motor_ain, HIGH);
          analogWrite(pin_motor_ain2_pwm, motor_max_speed/2);

          // When the timer runs out, stop motors and exit
          if ((currentMillis - startMillis >= period_90_deg) && currentMillis != startMillis)
          {
            MoveMotors(Stop);
            break;
          }
          // Save currentMillis for the next loop
          currentMillis = millis();
        }
        break;
      }
      case Stop:
      {
        // Left Bank
        digitalWrite(pin_motor_bin, LOW);
        analogWrite(pin_motor_bin2_pwm, 0);

        // Right bank
        digitalWrite(pin_motor_ain, LOW);
        analogWrite(pin_motor_ain2_pwm, 0);
        break;
      }
    }
  }
}