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
const int maxPulses = 3000; //Index and middle can do 3100

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

void normalize(float& value) {
  if (value > 1) {
    value = 1;
  }
  else if (value < 0) {
    value = 0;
  }
}

void receiveEvent() {
  if (Wire.available()) {
    uint8_t* byteArray = (uint8_t*) &percentage;

    for (int i = 0; i < 4; i++) {
      byteArray[i] = Wire.read();
    }
    normalize(percentage);
    target1 = (int) (maxPulses * percentage);

    for (int i = 0; i < 4; i++) {
      byteArray[i] = Wire.read();
    }
    normalize(percentage);
    target2 = (int) (maxPulses * percentage);

    for (int i = 0; i < 4; i++) {
      byteArray[i] = Wire.read();
    }
    normalize(percentage);
    target3 = (int) (maxPulses * percentage);

    for (int i = 0; i < 4; i++) {
      byteArray[i] = Wire.read();
    }
    normalize(percentage);
    target4 = (int) (maxPulses * percentage);
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