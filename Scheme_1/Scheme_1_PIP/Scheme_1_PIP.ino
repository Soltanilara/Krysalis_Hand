#include "Motor.h"

//Inputs
#define E1A 2
#define E1B 22
#define E2A 3
#define E2B 23
#define E3A 18
#define E3B 24
#define E4A 19
#define E4B 25

//Motor variables
#define SPEED 100

//Track the number of pulses from each motor
volatile int numPulsesA = 0;
volatile int numPulsesB = 0;
volatile int numPulsesC = 0;
volatile int numPulsesD = 0;

//Set the max number of pulses for each finger, which equates to number of rotations
#define maxPulsesPinky 1950
#define maxPulsesMiddleRing 2400
#define maxPulsesIndex 1750

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
  attachInterrupt(digitalPinToInterrupt(E1A), readPulsesA, RISING);
  attachInterrupt(digitalPinToInterrupt(E2A), readPulsesB, RISING);
  attachInterrupt(digitalPinToInterrupt(E3A), readPulsesC, RISING);
  attachInterrupt(digitalPinToInterrupt(E4A), readPulsesD, RISING);

  setupOutput();
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

//Returns true when it is still going;
bool setPosition(double percent) {
  int positionMiddleRing = (int) (maxPulsesMiddleRing * percent);
  int positionIndex = (int) (maxPulsesIndex * percent);
  int positionPinky = (int) (maxPulsesPinky * percent);
  bool incomplete = false;

  if (abs(numPulsesA - positionPinky) <= 5) {
    Set_PWMA(0);
  }
  else if (numPulsesA <= positionPinky) {
    Set_PWMA(SPEED);
    incomplete = true;
  }
  else {
    Set_PWMA(-SPEED);
    incomplete = true;
  }

  if (abs(numPulsesB - positionMiddleRing) <= 5) {
    Set_PWMB(0);
  }
  else if (numPulsesB <= positionMiddleRing) {
    Set_PWMB(SPEED);
    incomplete = true;
  }
  else {
    Set_PWMB(-SPEED);
    incomplete = true;
  }

  if (abs(numPulsesC - positionMiddleRing) <= 5) {
    Set_PWMC(0);
  }
  else if (numPulsesC <= positionMiddleRing) {
    Set_PWMC(SPEED);
    incomplete = true;
  }
  else {
    Set_PWMC(-SPEED);
    incomplete = true;
  }

  if (abs(numPulsesD - positionIndex) <= 5) {
    Set_PWMD(0);
  }
  else if (numPulsesD <= positionIndex) {
    Set_PWMD(SPEED);
    incomplete = true;
  }
  else {
    Set_PWMD(-SPEED);
    incomplete = true;
  }

  return incomplete;
}

void stop() {
  Set_PWMA(0);
  Set_PWMB(0);
  Set_PWMC(0);
  Set_PWMD(0);
}

void loop () {
  while (setPosition(1));
  Set_PWMA(0);
  delay(1000);
  while(setPosition(0));
  Set_PWMA(0);
  delay(1000);
}

