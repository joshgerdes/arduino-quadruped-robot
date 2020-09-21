#include <SoftwareSerial.h>
#include "src/libraries/ArduinoBlue/src/ArduinoBlue.h"
#include "src/libraries/VarSpeedServo/VarSpeedServo.h"

#define BAUD_RATE 9600
#define BLUETOOTH_TX 13
#define BLUETOOTH_RX 12
#define PIN_TRIG 2
#define PIN_ECHO 3
#define STOP_MAX 75
#define STOP_MIN 25
#define DISTANCE_MIN 10

int throttle, steering, button, distance;
int prevThrottle = 49;
int prevSteering = 49;
bool autonomous = false;

SoftwareSerial bluetooth(BLUETOOTH_TX, BLUETOOTH_RX);
ArduinoBlue phone(bluetooth);

VarSpeedServo servoFrontLeftFront;
VarSpeedServo servoFrontLeftBack;
VarSpeedServo servoFrontRightFront;
VarSpeedServo servoFrontRightBack;
VarSpeedServo servoBackLeftFront;
VarSpeedServo servoBackLeftBack;
VarSpeedServo servoBackRightFront;
VarSpeedServo servoBackRightBack;

void setup()
{
  delay(3000); // power-up safety delay

  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  Serial.begin(BAUD_RATE);
  bluetooth.begin(BAUD_RATE);
  delay(100);

  stand();

  Serial.println("Setup Complete");
}

void loop()
{
  button = phone.getButton();
  throttle = phone.getThrottle();
  steering = phone.getSteering();
  distance = getDistance();

  logging();

  if (button == 1)
  {
    autonomous = !autonomous;
    stand();
  }

  if (autonomous)
  {
    autonomousMode();
  }
  else
  {
    standardMode();
  }
}

void autonomousMode()
{
  if (distance > DISTANCE_MIN)
  {
    forward();
  }
  else
  {
    tilt();
    delay(1000);
    sit();
    delay(1000);
    stand();

    for (int i = 0; i < 5; i++)
    {
      right();
    }
  }
}

void standardMode()
{
  if (button != -1)
  {
    switch (button)
    {
    case 2:
      stand();
      break;
    case 3:
      lay();
      break;
    case 4:
      sit();
      break;
    case 5:
      crouch();
      break;
    case 6:
      tilt();
      break;
    case 7:
      for (int i = 0; i < 5; i++)
      {
        strut();
      }
      break;
    }
  }
  else if (steering >= STOP_MAX)
  {
    right();
  }
  else if (steering <= STOP_MIN)
  {
    left();
  }
  else if (throttle >= STOP_MAX)
  {
    forward();
  }
  else if (throttle <= STOP_MIN)
  {
    backward();
  }
  else if (prevThrottle != throttle && prevSteering != steering)
  {
    stand();
  }

  prevThrottle = throttle;
  prevSteering = steering;
}

void logging()
{
  Serial.print("Button: ");
  Serial.print(button);
  Serial.print(", Throttle: ");
  Serial.print(throttle);
  Serial.print(", Steering: ");
  Serial.print(steering);
  Serial.print(", Distance: ");
  Serial.print(distance);
  Serial.print(", Autonomous: ");
  Serial.println(autonomous ? "True" : "False");
}

int getDistance()
{
  // Clears the PIN_TRIG condition
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);

  // Sets the PIN_TRIG HIGH (ACTIVE) for 10 microseconds
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  // Reads the PIN_ECHO, returns the sound wave travel time in microseconds
  long duration = pulseIn(PIN_ECHO, HIGH);

  // Calculating the distance
  return duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
}

void servoAttach()
{
  servoFrontLeftFront.attach(4);
  servoFrontLeftBack.attach(5);
  servoFrontRightFront.attach(6);
  servoFrontRightBack.attach(7);
  servoBackLeftFront.attach(8);
  servoBackLeftBack.attach(9);
  servoBackRightFront.attach(10);
  servoBackRightBack.attach(11);
}

void servoDettach()
{
  servoFrontLeftFront.detach();
  servoFrontLeftBack.detach();
  servoFrontRightFront.detach();
  servoFrontRightBack.detach();
  servoBackLeftFront.detach();
  servoBackLeftBack.detach();
  servoBackRightFront.detach();
  servoBackRightBack.detach();
}

void move(int sFLF, int sFLB, int sFRF, int sFRB, int sBLF, int sBLB, int sBRF, int sBRB, int speed = 0, int delayed = 500, bool dettach = false)
{
  if (!servoFrontLeftFront.attached())
    servoAttach();

  servoFrontLeftFront.write(sFLF, speed);
  servoFrontLeftBack.write(sFLB, speed);
  servoFrontRightFront.write(sFRF, speed);
  servoFrontRightBack.write(sFRB, speed);
  servoBackLeftFront.write(sBLF, speed);
  servoBackLeftBack.write(sBLB, speed);
  servoBackRightFront.write(sBRF, speed);
  servoBackRightBack.write(sBRB, speed);

  delay(delayed);

  if (dettach)
    servoDettach();
}

void stand()
{
  move(180, 0, 0, 180, 180, 0, 0, 180, 0, 1000, true);
}

void lay()
{
  move(90, 90, 90, 90, 90, 90, 90, 90, 20, 2500, true);
}

void sit()
{
  move(180, 0, 0, 180, 45, 135, 135, 45, 150, true);
}

void crouch()
{
  move(45, 135, 135, 45, 180, 0, 0, 180, 150, true);
}

void tilt()
{
  int delayed = 400;
  int speed = 100;

  move(180, 0, 0, 180, 180, 0, 0, 180, 0, 1000);
  move(125, 55, 45, 135, 135, 45, 0, 180, speed, delayed);
  move(135, 45, 55, 125, 180, 0, 45, 135, speed, delayed);
  move(180, 0, 45, 135, 135, 45, 55, 125, speed, delayed);
  move(135, 45, 0, 180, 125, 55, 45, 135, speed, delayed);
  move(180, 0, 0, 180, 180, 0, 0, 180, 0, 1000, true);
}

void strut()
{
  int delayed = 150;

  move(180, 45, 0, 135, 180, 45, 0, 135, 0, delayed);
  move(90, 45, 0, 135, 180, 45, 90, 135, 0, delayed);
  move(135, 0, 0, 135, 180, 45, 45, 180, 0, delayed);
  move(180, 45, 0, 135, 180, 45, 0, 135, 0, delayed);
  move(180, 45, 90, 135, 90, 45, 0, 135, 0, delayed);
  move(180, 45, 45, 180, 135, 0, 0, 135, 0, delayed);
}

void forward()
{
  int delayed = 75;

  move(90, 135, 0, 135, 180, 45, 90, 45, 0, delayed);
  move(45, 0, 0, 135, 180, 45, 135, 180, 0, delayed);
  move(120, 0, 0, 135, 180, 45, 60, 180, 0, delayed);
  move(180, 45, 90, 45, 90, 135, 0, 135, 0, delayed);
  move(180, 45, 135, 180, 45, 0, 0, 135, 0, delayed);
  move(180, 45, 60, 180, 120, 0, 0, 135, 0, delayed);
}

void backward()
{
  int delayed = 75;

  move(45, 90, 45, 180, 135, 0, 135, 90, 0, delayed);
  move(180, 135, 45, 280, 235, 0, 0, 45, 0, delayed);
  move(180, 60, 45, 180, 135, 0, 0, 120, 0, delayed);
  move(135, 0, 135, 90, 45, 90, 45, 180, 0, delayed);
  move(135, 0, 0, 45, 180, 135, 45, 180, 0, delayed);
  move(135, 0, 0, 120, 180, 60, 45, 180, 0, delayed);
}

void left()
{
  int delayed = 75;

  move(0, 135, 90, 45, 45, 90, 135, 0, 0, delayed);
  move(0, 135, 135, 180, 180, 135, 135, 0, 0, delayed);
  move(0, 135, 60, 180, 180, 60, 135, 0, 0, delayed);
  move(90, 45, 0, 135, 135, 0, 45, 90, 0, delayed);
  move(135, 180, 0, 135, 135, 0, 180, 135, 0, delayed);
  move(60, 180, 0, 135, 135, 0, 180, 60, 0, delayed);
}

void right()
{
  int delayed = 75;

  move(90, 135, 180, 45, 45, 180, 135, 90, 0, delayed);
  move(45, 0, 180, 45, 45, 180, 0, 45, 0, delayed);
  move(120, 0, 180, 45, 45, 180, 0, 120, 0, delayed);
  move(180, 45, 90, 135, 135, 90, 45, 180, 0, delayed);
  move(180, 45, 45, 0, 0, 45, 45, 180, 0, delayed);
  move(180, 45, 120, 0, 0, 120, 45, 180, 0, delayed);
}
