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