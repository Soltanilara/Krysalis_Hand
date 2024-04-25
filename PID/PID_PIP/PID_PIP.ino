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
  Wire.begin(3);

  //I2C
  Wire.onReceive(receiveEvent);

  setupPosition();
  setupMotors();
}

void receiveEvent() {
  if (Wire.available()) {
    uint8_t* byteArray = (uint8_t*) &percentage;

    for (int i = 0; i < 4; i++) {
      byteArray[i] = Wire.read();
    }
    aTarget = (int) (maxPulsesMiddleRingPinky * percentage);

    for (int i = 0; i < 4; i++) {
      byteArray[i] = Wire.read();
    }
    bTarget = (int) (maxPulsesMiddleRingPinky * percentage);

    for (int i = 0; i < 4; i++) {
      byteArray[i] = Wire.read();
    }
    cTarget = (int) (maxPulsesMiddleRingPinky * percentage);

    for (int i = 0; i < 4; i++) {
      byteArray[i] = Wire.read();
    }
    dTarget = (int) (maxPulsesIndex * percentage);
  }
}


void loop() {
  setPosition();
}