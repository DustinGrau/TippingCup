/**
 * Matilda the Musical - Magical Tipping Cup
 */

#include <Servo.h>

const int analogPinA1 = A1;  // A1 pin for input
const int analogPinA2 = A2;  // A2 pin for input
const int servoPin = 9;     // Digital pin for servo control

Servo myServo;  // Create a servo object to control a servo motor

void setup() {
  pinMode(analogPinA1, INPUT);
  pinMode(analogPinA2, INPUT);
  myServo.attach(servoPin);
}

void loop() {
  // Read the analog inputs
  int sensorValueA1 = analogRead(analogPinA1);
  int sensorValueA2 = analogRead(analogPinA2);

  // Check if A1 is HIGH
  if (sensorValueA1 > 700) {
    // Turn the servo 90 degrees
    myServo.write(90);
    delay(500);  // Adjust delay as needed
  }

  // Check if A2 is HIGH
  if (sensorValueA2 > 700) {
    // Turn the servo -90 degrees
    myServo.write(-90);
    delay(500);  // Adjust delay as needed
  }
}
