#include <Servo.h>

#define SERVO_PIN 5
#define ECHO_PIN 2
#define TRIG_PIN 3

#define LED_RED 9
#define LED_GREEN 10
#define LED_BLUE 11

#define MIN_DISTANCE 5
#define MAX_DISTANCE 150
#define DELAY_PER_STEP 30
#define DEEGRES_PER_STEP 2

Servo servoMotor;

int servoDirection = 0;
int servoPosition = 0;
int objectDistante = 0;

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

void loop()
{
  servoDirection = 1;

  for (servoPosition = 0; servoPosition <= 180; servoPosition += DEEGRES_PER_STEP)
  {
    servoMotor.write(servoPosition);
    objectDistante = readUltrasonicSensor(TRIG_PIN, ECHO_PIN);
    printInfo(servoPosition, servoDirection, objectDistante);
    updateRGBIndicator(LED_RED, LED_GREEN, LED_BLUE, objectDistante, MIN_DISTANCE, MAX_DISTANCE);
    delay(DELAY_PER_STEP);
  }

  servoDirection = -1;

  for (servoPosition = 180 - DEEGRES_PER_STEP; servoPosition >= DEEGRES_PER_STEP; servoPosition -= DEEGRES_PER_STEP)
  {
    servoMotor.write(servoPosition);
    objectDistante = readUltrasonicSensor(TRIG_PIN, ECHO_PIN);
    printInfo(servoPosition, servoDirection, objectDistante);
    updateRGBIndicator(LED_RED, LED_GREEN, LED_BLUE, objectDistante, MIN_DISTANCE, MAX_DISTANCE);
    delay(DELAY_PER_STEP);
  }
}

int readUltrasonicSensor(int trig, int echo)
{
  int pulseDuration;
  int objectDistante;

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  pulseDuration = pulseIn(echo, HIGH);
  objectDistante = pulseDuration * 0.034 / 2;

  if (objectDistante < MIN_DISTANCE || objectDistante > MAX_DISTANCE)
  {
    return -1;
  }
  else
  {
    return objectDistante;
  }
}

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

String printInfo(int servoPosition, int servoDirection, int objectDistance)
{
  Serial.print(servoPosition);
  Serial.print(",");
  Serial.print(servoDirection);
  Serial.print(",");
  Serial.println(objectDistance);
}

void turnOffRGB(int pinR, int pinG, int pinB)
{
  digitalWrite(pinR, LOW);
  digitalWrite(pinG, LOW);
  digitalWrite(pinB, LOW);
}

void writeRGB(int pinR, int pinG, int pinB, int R, int G, int B)
{
  turnOffRGB(pinR, pinG, pinB);
  digitalWrite(pinR, R);
  digitalWrite(pinG, G);
  digitalWrite(pinB, B);
}

void sayHello()
{
  servoMotor.write(90);
  writeRGB(LED_RED, LED_GREEN, LED_BLUE, 255, 0, 120);
  delay(400);
  servoMotor.write(0);
  writeRGB(LED_RED, LED_GREEN, LED_BLUE, 0, 255, 0);
  delay(400);
  servoMotor.write(180);
  writeRGB(LED_RED, LED_GREEN, LED_BLUE, 0, 0, 255);
  delay(400);
  servoMotor.write(60);
  writeRGB(LED_RED, LED_GREEN, LED_BLUE, 255, 0, 120);
  delay(200);
  servoMotor.write(120);
  writeRGB(LED_RED, LED_GREEN, LED_BLUE, 0, 255, 0);
  delay(200);
  servoMotor.write(60);
  writeRGB(LED_RED, LED_GREEN, LED_BLUE, 0, 0, 255);
  delay(200);
  servoMotor.write(120);
  writeRGB(LED_RED, LED_GREEN, LED_BLUE, 255, 0, 0);
  delay(200);
  servoMotor.write(60);
  writeRGB(LED_RED, LED_GREEN, LED_BLUE, 0, 0, 255);
  delay(200);
  servoMotor.write(120);
  writeRGB(LED_RED, LED_GREEN, LED_BLUE, 255, 0, 0);
  delay(200);
  servoMotor.write(90);
  writeRGB(LED_RED, LED_GREEN, LED_BLUE, 255, 0, 0);
  delay(1000);
  turnOffRGB(LED_RED, LED_GREEN, LED_BLUE);
}