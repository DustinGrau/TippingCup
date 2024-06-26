/**
 * Tipping Cup Prop
 * Detects voltage from specific pins on an Arduino Nano from an RC remote receiver.
 * Can operate in a "wobble" mode or fully "tip" when mounted inside a tall object.
 */

#include <Servo.h>

const int analogPinA1 = A1; // A1 pin, maps to the DOWN or RIGHT button on remote
const int analogPinA2 = A2; // A2 pin, maps to the UP or LEFT button on remote
const int analogPinA5 = A5; // A5 pin, maps to the TOGGLE button on remote
const int servoPin = 9;     // Digital pin for servo control (D9)
const int highThresh = 500; // Threshold for considering a pin as HIGH 
uint16_t servoPos = 0;      // Last-known servo position
boolean b_tipped = false;   // Indicates whether the servo was just in the "tipped" state.

Servo mainServo; // Create a servo object to control a servo motor

void setup() {
  Serial.begin(9600);

  pinMode(analogPinA1, INPUT);
  pinMode(analogPinA2, INPUT);
  pinMode(analogPinA5, INPUT);

  mainServo.attach(servoPin);
  delay(10);
  mainServo.write(0); // Reset to a known position
}

void loop() {
  // Read the analog values from the input pins.
  int sensorValueA1 = analogRead(analogPinA1);
  int sensorValueA2 = analogRead(analogPinA2);
  int sensorValueA5 = analogRead(analogPinA5);

  // Check if A5 is HIGH, meaning the device
  // should be doing a wobble action
  if (sensorValueA5 > highThresh) {
    // Move the servo some random angle, over some random period, every 10ms
    servoPos = moveServo(random(20, 45), random(200, 400), 10);
    delay(random(100, 300)); // Delay before next action

    // Add a very small movement at the peak of the last angle
    servoPos = moveServo(servoPos + 5, 300, 10);
    delay(random(200, 300)); // Delay before next action

    // Always reset to the default (upright) position, slowly
    servoPos = moveServo(0, 600, 10);
    delay(random(300, 500)); // Delay before next action
  } else {
    // Check if A1 is HIGH (reset)
    if (sensorValueA1 > highThresh) {
      if (resetPosition()) {
        delay(500); // Delay before next action
      }

      // Reset for next tipping event
      b_tipped = false;
    }

    // Check if A2 is HIGH (tip)
    if (sensorValueA2 > highThresh && !b_tipped) {
      // Immediately rotate the servo 180 degrees (tipped)
      servoPos = moveServo(180, 100, 10);
      delay(500); // Delay before next action

      // Return to a reset position
      if (resetPosition()) {
        delay(1000); // Delay before next action
      }

      // Set latch to ensure sensor state only
      // causes a single servo/tipping event
      b_tipped = true;
    }
  }
}

uint16_t moveServo(uint16_t i_servo_angle, uint16_t i_move_time, uint16_t i_step_time) {
  unsigned long startTime = millis(); // Get the current time

  while (millis() - startTime < i_move_time) {
    // Move the servo gradually to the target position
    int currentPos = map(millis(), startTime, startTime + i_move_time, servoPos, i_servo_angle);
    mainServo.write(currentPos);
    delay(i_step_time); // Adjust the delay to control the speed of the movement
  }

  mainServo.write(i_servo_angle); // Ensure the servo reaches the exact target position

  return i_servo_angle; // Return the new target position for the servo
}

boolean resetPosition() {
  boolean b_changed = false;

  // Immediately return the servo to 0 degrees (fully upright)
  if(mainServo.read() > 0) {
    mainServo.write(0); // Sets the desired position
    servoPos = mainServo.read(); // Confirm position
    b_changed = true; // Indicate change of position
  }

  return b_changed;
}