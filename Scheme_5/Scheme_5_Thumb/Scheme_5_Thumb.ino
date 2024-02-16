#include <Wire.h>
#include "Motor.h"

//Inputs
//A is MCP, B is IP, C is CMC
#define E1A 18
#define E1B 24
#define E2A 2
#define E2B 22
#define E3A 3
#define E3B 23

//Motor variables
#define SPEED 255

//Track the number of pulses from each motor
volatile int numPulsesA = 0;
volatile int numPulsesB = 0;
volatile int numPulsesC = 0;

//Set the max and min number of pulses, which equates to number of rotations
int maxPulsesIP = 1200;
int maxPulsesMCP = 1600;
int maxPulsesCMC = 20;

//Rotation percentage
volatile float percentage = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin(1);

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
  attachInterrupt(digitalPinToInterrupt(E1A), readPulsesA, RISING);
  attachInterrupt(digitalPinToInterrupt(E2A), readPulsesB, RISING);
  attachInterrupt(digitalPinToInterrupt(E3A), readPulsesC, RISING);

  setupMotors();
}

void receiveEvent() {
  if (Wire.available()) {
    uint8_t* byteArray = (uint8_t*) &percentage;

    for (int i = 0; i < 4; i++) {
      byteArray[i] = Wire.read();
    }

    // Serial.println(percentage);
  }
}

void requestEvent() {
  int aPosition = (int) (maxPulsesCMC * percentage);
  int bPosition = (int) (maxPulsesMCP * percentage);
  int cPosition = (int) (maxPulsesIP * percentage);

  bool aComplete = abs(numPulsesA - aPosition) < 3;
  bool bComplete = abs(numPulsesB - bPosition) < 20;
  bool cComplete = abs(numPulsesC - cPosition) < 20;

  Wire.write(aComplete && bComplete && cComplete);
}

//Read the pulses of motor A
void readPulsesA() {
  int b = digitalRead(E1B);

  if (b > 0) {
    numPulsesA--;
  }
  else {
    numPulsesA++;
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

void setPosition() {
  int aPosition = (int) (maxPulsesCMC * percentage);
  int bPosition = (int) (maxPulsesMCP * percentage);
  int cPosition = (int) (maxPulsesIP * percentage);

  if (abs(numPulsesA - aPosition) < 3) {
    Set_PWMA(0);
    Serial.println();
  }
  else if (numPulsesA > aPosition) {
    Set_PWMA(-80);
  }
  //numPulsesA < minPulses
  else {
    Set_PWMA(120);
  }

  if (abs(numPulsesB - bPosition) < 20) {
    Set_PWMB(0);
    // Serial.println();
  }
  else if (numPulsesB > bPosition) {
    Set_PWMB(-SPEED);
  }
  //numPulsesC < minPulses
  else {
    Set_PWMB(SPEED);
  }

  if (abs(numPulsesC - cPosition) < 20) {
    Set_PWMC(0);
  }
  else if (numPulsesC > cPosition) {
    Set_PWMC(-SPEED);
  }
  //numPulsesC < minPulses
  else {
    Set_PWMC(SPEED);
  }
}

void loop() {
  setPosition();
}