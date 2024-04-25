#include <Wire.h>
#include "Motor.h"
#include "Position.h"

//Pulses from each motor
extern volatile int numPulsesA;
extern volatile int numPulsesB;
extern volatile int numPulsesC;
extern volatile int numPulsesD;

//Targets for each motor
extern volatile int target1;
extern volatile int target2;
extern volatile int target3;
extern volatile int target4;

//Set the max and min number of pulses, which equates to number of rotations
const int maxPulses = 2300;

float percentage = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin(4);

  //I2C
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

  setupPosition();
  setupMotors();
}

void receiveEvent() {
  if (Wire.available()) {
    uint8_t* byteArray = (uint8_t*) &percentage;

    for (int i = 0; i < 4; i++) {
      byteArray[i] = Wire.read();
    }
    target1 = (int) (percentage * maxPulses);

    for (int i = 0; i < 4; i++) {
      byteArray[i] = Wire.read();
    }
    target2 = (int) (percentage * maxPulses);

    for (int i = 0; i < 4; i++) {
      byteArray[i] = Wire.read();
    }
    target3 = (int) (percentage * maxPulses);

    for (int i = 0; i < 4; i++) {
      byteArray[i] = Wire.read();
    }
    target4 = (int) (percentage * maxPulses);
  }
}

void requestEvent() {
  bool aComplete = abs(numPulsesA - target1) < 10;
  bool bComplete = abs(numPulsesB - target2) < 10;
  bool cComplete = abs(numPulsesC - target3) < 10;
  bool dComplete = abs(numPulsesD - target4) < 10;

  Wire.write(aComplete && bComplete && cComplete && dComplete);
}

void loop() {
  setPosition();
}