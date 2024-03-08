#include <Wire.h>
#include "Motor.h"
#include "Position.h"

//Track the number of pulses from each motor
extern volatile int numPulsesA;
extern volatile int numPulsesB;
extern volatile int numPulsesC;

//Targets for each motor
extern volatile int aTarget;
extern volatile int bTarget;
extern volatile int cTarget;

//Set the max and min number of pulses, which equates to number of rotations
const int maxPulsesIP = 1200;
const int maxPulsesMCP = 1600;
const int maxPulsesCMC = 20;

float percentage = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin(1);

  //I2C
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

  setupPosition();
  setupMotors();
}

void receiveEvent() {
  if (Wire.available()) {
    float prevPercentage = percentage;
    uint8_t* byteArray = (uint8_t*) &percentage;

    for (int i = 0; i < 4; i++) {
      byteArray[i] = Wire.read();
    }

    if (prevPercentage != percentage) {
      aTarget = (int) (maxPulsesCMC * percentage);
      bTarget = (int) (maxPulsesMCP * percentage);
      cTarget = (int) (maxPulsesIP * percentage);
    }
  }
}

void requestEvent() {
  bool aComplete = abs(numPulsesA - aTarget) < 3;
  bool bComplete = abs(numPulsesB - bTarget) < 10;
  bool cComplete = abs(numPulsesC - cTarget) < 10;

  // Wire.write(aComplete && bComplete && cComplete);
  Wire.write(bComplete && cComplete);
}

void loop() {
  setPosition();
}