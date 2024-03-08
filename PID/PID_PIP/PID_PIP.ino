#include <Wire.h>
#include "Motor.h"
#include "Position.h"

//Pulses from each motor
extern volatile int numPulsesA;
extern volatile int numPulsesB;
extern volatile int numPulsesC;
extern volatile int numPulsesD;

//Targets for each motor
extern volatile int aTarget;
extern volatile int bTarget;
extern volatile int cTarget;
extern volatile int dTarget;

//Set the max and min number of pulses, which equates to number of rotations
int maxPulsesMiddleRingPinky = 2300;
int maxPulsesIndex = 1900;

float percentage = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin(2);

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
      aTarget = (int) (maxPulsesMiddleRingPinky * percentage);
      bTarget = (int) (maxPulsesMiddleRingPinky * percentage);
      cTarget = (int) (maxPulsesMiddleRingPinky * percentage);
      dTarget = (int) (maxPulsesIndex * percentage);
    }
  }
}

void requestEvent() {
  bool aComplete = abs(numPulsesA - aTarget) < 10;
  bool bComplete = abs(numPulsesB - bTarget) < 10;
  bool cComplete = abs(numPulsesC - cTarget) < 10;
  bool dComplete = abs(numPulsesD - dTarget) < 10;

  Wire.write(aComplete && bComplete && cComplete && dComplete);
}

void loop() {
  setPosition();
}