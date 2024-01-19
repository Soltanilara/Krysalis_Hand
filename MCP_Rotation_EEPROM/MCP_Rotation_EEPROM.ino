#include <EEPROM.h>
#include "Memory.h"

//Inputs
#define E1A 2
#define E1B 22
#define E2A 3
#define E2B 23
#define E3A 18
#define E3B 24
#define E4A 19
#define E4B 25
#define button 12

//Outputs
#define AIN1 4
#define AIN2 5
#define BIN1 6
#define BIN2 7
#define CIN1 8
#define CIN2 9
#define DIN1 10
#define DIN2 11

//Motor variables
#define SPEED 100

//Define the state
enum state:byte {
  CONTRACTING = 0,
  EXTENDING = 1,
  BREAK = 2
};

volatile state currentState = CONTRACTING;

//Track the number of pulses from each motor
volatile int numPulsesA = 0;
volatile int numPulsesB = 0;
volatile int numPulsesC = 0;
volatile int numPulsesD = 0;

//Set the max and min number of pulses, which equates to number of rotations
int maxPulsesCWMiddleRing = 2000;
int maxPulsesPinky = 2500;
int maxPulsesIndex = 2600;
int maxPulsesCCW = 0;

//Have the respective motors finished their cycles yet?
bool aComplete = false;
bool bComplete = false;
bool cComplete = false;
bool dComplete = false;

void setup() {
  Serial.begin(9600);

  //Input setting
  pinMode(E1A, INPUT);
  pinMode(E1B, INPUT);
  pinMode(E2A, INPUT);
  pinMode(E2B, INPUT);
  pinMode(E3A, INPUT);
  pinMode(E3B, INPUT);
  pinMode(E4A, INPUT);
  pinMode(E4B, INPUT);
  pinMode(button, INPUT);
  attachInterrupt(digitalPinToInterrupt(E1A), readPulsesA, RISING);
  attachInterrupt(digitalPinToInterrupt(E2A), readPulsesB, RISING);
  attachInterrupt(digitalPinToInterrupt(E3A), readPulsesC, RISING);
  attachInterrupt(digitalPinToInterrupt(E4A), readPulsesD, RISING);

  //Output setting
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(CIN1, OUTPUT);
  pinMode(CIN2, OUTPUT);
  pinMode(DIN1, OUTPUT);
  pinMode(DIN2, OUTPUT);

  //First set all the pins to low
  analogWrite(AIN1, LOW);
  analogWrite(AIN2, LOW);
  analogWrite(BIN1, LOW);
  analogWrite(BIN2, LOW);
  analogWrite(CIN1, LOW);
  analogWrite(CIN2, LOW);
  analogWrite(DIN1, LOW);
  analogWrite(DIN2, LOW);

  if (EEPROM.read(0) == 255) {
    currentState = CONTRACTING;
  }
  else {
    currentState = EEPROM.read(0);
  }

  numPulsesA = readMemory(1);
  numPulsesB = readMemory(5);
  numPulsesC = readMemory(9);
  numPulsesD = readMemory(13);
}

void stop() {
  EEPROM.write(0, currentState);

  Set_PWMA(0);
  Set_PWMB(0);
  Set_PWMC(0);
  Set_PWMD(0);

  currentState = BREAK;

  writeToMemory(1, numPulsesA);
  writeToMemory(5, numPulsesB);
  writeToMemory(9, numPulsesC);
  writeToMemory(13, numPulsesD);
}

//Read the pulses of motor A
void readPulsesA() {
  int b = digitalRead(E1B);

  if (b > 0) {
    numPulsesA++;
  }
  else {
    numPulsesA--;
  }
}

//Read the pulses of motor B
void readPulsesB() {
  int b = digitalRead(E2B);

  if (b > 0) {
    numPulsesB++;
  }
  else {
    numPulsesB--;
  }
}

//Read the pulses of motor C
void readPulsesC() {
  int b = digitalRead(E3B);

  if (b > 0) {
    numPulsesC++;
  }
  else {
    numPulsesC--;
  }
}

//Read the pulses of motor D
void readPulsesD() {
  int b = digitalRead(E4B);

  if (b > 0) {
    numPulsesD++;
  }
  else {
    numPulsesD--;
  }
}

//Set the speed of motor A
void Set_PWMA(int pwm)
{
  if(pwm>0)
  {
    analogWrite(AIN1, 255 - pwm);
    analogWrite(AIN2, 255);
  }
  else
  {
    analogWrite(AIN1, 255);
    analogWrite(AIN2, 255 + pwm);
  }
}

//Set the speed of motor B
void Set_PWMB(int pwm)
{
  if(pwm>0)
  {
    analogWrite(BIN1, 255 - pwm);
    analogWrite(BIN2, 255);
  }
  else
  {
    analogWrite(BIN1, 255);
    analogWrite(BIN2, 255 + pwm);
  }
}

//Set the speed of motor C
void Set_PWMC(int pwm)
{
  if(pwm>0)
  {
    analogWrite(CIN1, 255 - pwm);
    analogWrite(CIN2, 255);
  }
  else
  {
    analogWrite(CIN1, 255);
    analogWrite(CIN2, 255 + pwm);
  }
}

//Set the speed of motor D
void Set_PWMD(int pwm)
{
  if(pwm>0)
  {
    analogWrite(DIN1, 255 - pwm);
    analogWrite(DIN2, 255);
  }
  else
  {
    analogWrite(DIN1, 255);
    analogWrite(DIN2, 255 + pwm);
  }
}

void loop() {
  if (digitalRead(button) == HIGH) {
    stop();
  }

  switch (currentState) {
    case CONTRACTING:
      if (numPulsesA <= maxPulsesPinky) {
        Set_PWMA(SPEED);
      }
      else {
        Set_PWMA(0);
        aComplete = true;
      }

      if (numPulsesB <= maxPulsesCWMiddleRing) {
        Set_PWMB(SPEED);
      }
      else {
        Set_PWMB(0);
        bComplete = true;
      }

      if (numPulsesC <= maxPulsesCWMiddleRing) {
        Set_PWMC(SPEED);
      }
      else {
        Set_PWMC(0);
        cComplete = true;
      }

      if (numPulsesD <= maxPulsesIndex) {
        Set_PWMD(SPEED);
      }
      else {
        Set_PWMD(0);
        dComplete = true;
      }

      if (aComplete && bComplete && cComplete && dComplete) {
        delay(1000);

        aComplete = false;
        bComplete = false;
        cComplete = false;
        dComplete = false;

        currentState = EXTENDING;
      }
      break;

    case EXTENDING:
      if (numPulsesA > maxPulsesCCW) {
        Set_PWMA(-SPEED);
      }
      else {
        Set_PWMA(0);
        aComplete = true;
      }

      if (numPulsesB > maxPulsesCCW) {
        Set_PWMB(-SPEED);
      }
      else {
        Set_PWMB(0);
        bComplete = true;
      }

      if (numPulsesC > maxPulsesCCW) {
        Set_PWMC(-SPEED);
      }
      else {
        Set_PWMC(0);
        cComplete = true;
      }

      if (numPulsesD > maxPulsesCCW) {
        Set_PWMD(-SPEED);
      }
      else {
        Set_PWMD(0);
        dComplete = true;
      }
    
      if (aComplete && bComplete && cComplete && dComplete) {
        delay(1000);

        aComplete = false;
        bComplete = false;
        cComplete = false;
        dComplete = false;

        currentState = CONTRACTING;
      }
      break;
    Serial.println(numPulsesD);
  }
}
