/**
 * Matilda the Musical - Magical Tipping Cup
 */

#include <Servo.h>

const int analogPinA1 = A1; // A1 pin, maps to the DOWN or RIGHT button on remote
const int analogPinA2 = A2; // A2 pin, maps to the UP or LEFT button on remote
const int analogPinA5 = A5; // A5 pin, maps to the TOGGLE button on remote
const int servoPin = 9;     // Digital pin for servo control (D9)
uint16_t servoPos = 0;      // Last-known servo position
boolean b_tipped = false;   // Indicates whether the servo was just in the "tipped" state.

Servo mainServo; // Create a servo object to control a servo motor

void setup() {
  pinMode(analogPinA1, INPUT);
  pinMode(analogPinA2, INPUT);
  pinMode(analogPinA5, INPUT);

  mainServo.attach(servoPin);
  delay(10);
  mainServo.write(0); // Reset to a known position
}

void loop() {
  // Read the analog inputs
  int sensorValueA1 = analogRead(analogPinA1);
  int sensorValueA2 = analogRead(analogPinA2);
  int sensorValueA5 = analogRead(analogPinA5);

  // Check if A5 is HIGH, meaning the device
  // should be doing a wobble action
  if (sensorValueA5 > 600) {
    // Move the servo some random angle, over some random period, every 20ms
    servoPos = moveServo(random(20,60), random(200,400), 10);
    delay(random(100,400)); // Delay before next action

    // Always reset to the default (upright) position, slowly
    servoPos = moveServo(0, 500, 10);
    delay(random(200,500)); // Delay before next action
  } else {
    // Check if A1 is HIGH (reset)
    if (sensorValueA1 > 600) {
      resetPosition();
      delay(500); // Delay before next action
      b_tipped = false; // Reset for next tipping event
    }

    // Check if A2 is HIGH (tip)
    if (sensorValueA2 > 600 && !b_tipped) {
      // Immediately rotate the servo 180 degrees (tipped)
      mainServo.write(180);
      servoPos = mainServo.read();
      delay(500); // Delay before next action

      // Return to a reset position
      resetPosition();
      delay(1000); // Delay before next action

      // Set latch to ensure sensor state only
      // causes a single servo/tipping event
      b_tipped = true;
    }
  }
}

uint16_t moveServo(uint16_t i_servo_angle, uint16_t i_move_time, uint16_t i_step_time) {
  resetPosition(); // First reset to a known 0 angle

  unsigned long startTime = millis(); // Get the current time

  while (millis() - startTime < i_move_time) {
    // Move the servo gradually to the target position
    int currentPos = map(millis(), startTime, startTime + i_move_time, 0, i_servo_angle);
    mainServo.write(currentPos);
    delay(i_step_time); // Adjust the delay to control the speed of the movement
  }

  mainServo.write(i_servo_angle); // Ensure the servo reaches the exact target position

  return i_servo_angle; // Return the new target position for the servo
}

boolean resetPosition() {
  boolean b_changed = false;

  // Return the servo to 0 degrees (upright)
  if(mainServo.read() > 0) {
    servoPos = 0;
    b_changed = true;
    mainServo.write(servoPos);
  }

  return b_changed;
}