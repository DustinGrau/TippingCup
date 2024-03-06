/**
 * Matilda the Musical - Magical Tipping Cup
 */

#include <Servo.h>

const int analogPinA1 = A1; // A1 pin, maps to the DOWN or RIGHT button on remote
const int analogPinA2 = A2; // A2 pin, maps to the UP or LEFT button on remote
const int analogPinA5 = A5; // A5 pin, maps to the TOGGLE button on remote
const int servoPin = 9;     // Digital pin for servo control (D9)
int servoPos = 0;           // Last-known servo position

Servo mainServo; // Create a servo object to control a servo motor

void setup() {
  pinMode(analogPinA1, INPUT);
  pinMode(analogPinA2, INPUT);
  pinMode(analogPinA5, INPUT);

  mainServo.attach(servoPin);
  delay(10);
  mainServo.write(0); // Reset to a known position.
}

void loop() {
  // Read the analog inputs
  int sensorValueA1 = analogRead(analogPinA1);
  int sensorValueA2 = analogRead(analogPinA2);
  int sensorValueA5 = analogRead(analogPinA5);

  // Check if A5 is HIGH, meaning the device
  // should be doing a wobble action
  if (sensorValueA5 > 600) {
    if (servoPos > 0) {
      // Always reset if anything other than
      // the default (upright) position.
      servoPos = 0;
      mainServo.write(servoPos);
      delay(random(100,300)); // Delay before next action
    }

    servoPos = random(40,80);
    mainServo.write(servoPos);
    delay(random(200,400)); // Delay before next action
  } else {
    // Check if A1 is HIGH
    if (sensorValueA1 > 600) {
      // Return the servo to 0 degrees (upright)
      servoPos = 0;
      mainServo.write(servoPos);
      delay(500); // Delay before next input
    }

    // Check if A2 is HIGH
    if (sensorValueA2 > 600) {
      // Turn the servo 180 degrees (tipped)
      servoPos = 180;
      mainServo.write(servoPos);
      delay(500); // Delay before next input
    }
  }
}
