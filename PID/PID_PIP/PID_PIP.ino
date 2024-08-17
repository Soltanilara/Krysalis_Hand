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
const int maxPulses = 3000;

float percentage = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin(3);

  //I2C
  Wire.onReceive(receiveEvent);

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
    aTarget = (int) (maxPulses * percentage);

    for (int i = 0; i < 4; i++) {
      byteArray[i] = Wire.read();
    }
    normalize(percentage);
    bTarget = (int) (maxPulses * percentage);

    for (int i = 0; i < 4; i++) {
      byteArray[i] = Wire.read();
    }
    normalize(percentage);
    cTarget = (int) (maxPulses * percentage);

    for (int i = 0; i < 4; i++) {
      byteArray[i] = Wire.read();
    }
    normalize(percentage);
    dTarget = (int) (maxPulses * percentage);
  }
}


void loop() {
  setPosition();
}