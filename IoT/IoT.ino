/*
  IoT.ino - IoT project for object detection using an ultrasonic sensor and a servo motor
  Created by Jose Gómez, Daniel Lujan, and Emanuel López, May 2024
  Released under MIT License
*/

#include <Servo.h>
#include <NewPing.h>

#define SERVO_PIN 5
#define ECHO_PIN 2
#define TRIG_PIN 3

#define LED_RED 9
#define LED_GREEN 10
#define LED_BLUE 11

#define MIN_DISTANCE 2
#define MAX_DISTANCE 50
#define DELAY_PER_STEP 30
#define DEEGRES_PER_STEP 2

Servo servoMotor;
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

int servoDirection = 0;
int servoPosition = 0;
int objectDistante = 0;

/*
  Setup function
  Initializes the servo motor, ultrasonic sensor, and RGB LED
*/
void setup()
{
  servoMotor.attach(SERVO_PIN);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  Serial.begin(9600);
  sayHello();
}

/*
  Loop function
  Moves the servo motor from 0 to 180 degrees and back, reading the ultrasonic sensor and updating the RGB LED
*/
void loop()
{
  servoDirection = 1;

  for (servoPosition = 0; servoPosition <= 180; servoPosition += DEEGRES_PER_STEP)
  {
    servoMotor.write(servoPosition);
    objectDistante = readUltrasonicSensor();
    printInfo(servoPosition, servoDirection, objectDistante);
    updateRGBIndicator(LED_RED, LED_GREEN, LED_BLUE, objectDistante, MIN_DISTANCE, MAX_DISTANCE);
    delay(DELAY_PER_STEP);
  }

  servoDirection = -1;

  for (servoPosition = 180 - DEEGRES_PER_STEP; servoPosition >= DEEGRES_PER_STEP; servoPosition -= DEEGRES_PER_STEP)
  {
    servoMotor.write(servoPosition);
    objectDistante = readUltrasonicSensor();
    printInfo(servoPosition, servoDirection, objectDistante);
    updateRGBIndicator(LED_RED, LED_GREEN, LED_BLUE, objectDistante, MIN_DISTANCE, MAX_DISTANCE);
    delay(DELAY_PER_STEP);
  }
}

/*
  Function to read the ultrasonic sensor and return the distance in centimeters

  Returns:
    The distance in centimeters, or -1 if no object is detected
*/
int readUltrasonicSensor()
{
  int pulseDuration;
  int objectDistante;

  unsigned int uS = sonar.ping();
  objectDistante = uS / US_ROUNDTRIP_CM;

  if (objectDistante == 0)
  {
    return -1;
  }
  else
  {
    return objectDistante;
  }
}

/*
  Function to update the RGB LED based on the distance read by the ultrasonic sensor

  Parameters:
    pinR: The pin number for the red LED
    pinG: The pin number for the green LED
    pinB: The pin number for the blue LED
    val: The value to map to the RGB LED
    minVal: The minimum value for the mapping
    maxVal: The maximum value for the mapping
*/
void updateRGBIndicator(int pinR, int pinG, int pinB, int val, int minVal, int maxVal)
{
  int mappedVal = map(val, minVal, maxVal, 0, 100);

  if (val == -1)
  {
    writeRGB(pinR, pinG, pinB, 140, 0, 75);
  }
  else
  {
    if (mappedVal < 15)
    {
      writeRGB(pinR, pinG, pinB, 255, 0, 0);
    }
    else if (mappedVal >= 15 && mappedVal < 40)
    {
      writeRGB(pinR, pinG, pinB, 0, 0, 255);
    }
    else
    {
      writeRGB(pinR, pinG, pinB, 0, 255, 0);
    }
  }
}

/*
  Function to print the servo position, direction, and object distance to the serial monitor

  Parameters:
    servoPosition: The current position of the servo motor
    servoDirection: The direction the servo motor is moving
    objectDistance: The distance read by the ultrasonic sensor
*/
String printInfo(int servoPosition, int servoDirection, int objectDistance)
{
  Serial.print(servoPosition);
  Serial.print(",");
  Serial.print(servoDirection);
  Serial.print(",");
  Serial.println(objectDistance);
}

/*
  Function to turn off the RGB LED

  Parameters:
    pinR: The pin number for the red LED
    pinG: The pin number for the green LED
    pinB: The pin number for the blue LED
*/
void turnOffRGB(int pinR, int pinG, int pinB)
{
  digitalWrite(pinR, LOW);
  digitalWrite(pinG, LOW);
  digitalWrite(pinB, LOW);
}

/*
  Function to write to the RGB LED

  Parameters:
    pinR: The pin number for the red LED
    pinG: The pin number for the green LED
    pinB: The pin number for the blue LED
    R: The value for the red LED
    G: The value for the green LED
    B: The value for the blue LED
*/
void writeRGB(int pinR, int pinG, int pinB, int R, int G, int B)
{
  turnOffRGB(pinR, pinG, pinB);
  digitalWrite(pinR, R);
  digitalWrite(pinG, G);
  digitalWrite(pinB, B);
}

/*
  Function to move the servo motor to the initial position and display a greeting sequence
*/
void sayHello()
{
  int servoPositions[] = {0, 90, 180, 60, 120, 60, 120, 90};
  int delayTimes[] = {400, 400, 400, 200, 200, 200, 200, 200};
  int RGBColors[][3] = {{255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 0, 120}, {0, 255, 0}, {0, 0, 255}, {255, 0, 0}, {0, 0, 255}};

  for (int i = 0; i < 9; i++)
  {
    servoMotor.write(servoPositions[i]);
    writeRGB(LED_RED, LED_GREEN, LED_BLUE, RGBColors[i][0], RGBColors[i][1], RGBColors[i][2]);
    delay(delayTimes[i]);
  }

  delay(1000);
  turnOffRGB(LED_RED, LED_GREEN, LED_BLUE);
}