#include <Wire.h>
#include "Motor.h"

//Inputs
//A is MCP, B is IP, C is CMC
#define E1A 2
#define E1B 22
#define E2A 3
#define E2B 23
#define E3A 18
#define E3B 24
#define E4A 19
#define E4B 25

//Motor variables
#define SPEED 255

//Track the number of pulses from each motor
volatile int numPulsesA = 0;
volatile int numPulsesB = 0;
volatile int numPulsesC = 0;
volatile int numPulsesD = 0;

//Set the max and min number of pulses, which equates to number of rotations
int maxPulses = 2300;

volatile float percentage = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin(4);

  //I2C
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

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

  setupMotors();
}

void receiveEvent() {
  if (Wire.available()) {
    uint8_t* byteArray = (uint8_t*) &percentage;

    for (int i = 0; i < 4; i++) {
      byteArray[i] = Wire.read();
    }
  }
}

void requestEvent() {
  int position = (int) (maxPulses * percentage);

  bool aComplete = abs(numPulsesA - position) < 20;
  bool bComplete = abs(numPulsesB - position) < 20;
  bool cComplete = abs(numPulsesC - position) < 20;
  bool dComplete = abs(numPulsesD - position) < 20;

  Wire.write(aComplete && bComplete && cComplete && dComplete);
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

void setPosition() {
  int position = (int) (maxPulses * percentage);

  if (abs(numPulsesA - position) < 20) {
    Set_PWMA(0);
    // Serial.println();
  }
  else if (numPulsesA > position) {
    Set_PWMA(-SPEED);
  }
  //numPulsesC < minPulses
  else {
    Set_PWMA(SPEED);
  }

  if (abs(numPulsesB - position) < 20) {
    Set_PWMB(0);
    // Serial.println();
  }
  else if (numPulsesB > position) {
    Set_PWMB(-SPEED);
  }
  //numPulsesC < minPulses
  else {
    Set_PWMB(SPEED);
  }

  if (abs(numPulsesC - position) < 20) {
    Set_PWMC(0);
  }
  else if (numPulsesC > position) {
    Set_PWMC(-SPEED);
  }
  //numPulsesC < minPulses
  else {
    Set_PWMC(SPEED);
  }

  if (abs(numPulsesD - position) < 20) {
    Set_PWMD(0);
  }
  else if (numPulsesD > position) {
    Set_PWMD(-SPEED);
  }
  //numPulsesD < minPulses
  else {
    Set_PWMD(SPEED);
  }
}

void loop() {
 setPosition();
}