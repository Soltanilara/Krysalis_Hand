#include <Wire.h>
// #include "I2C.h"

enum state {
  CONTRACT_FINGERS,
  CONTRACT_THUMB,
  EXTEND_THUMB,
  EXTEND_FINGERS,
};

state currentState = CONTRACT_FINGERS;

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

bool ThumbDone() {
  Wire.requestFrom(1, 1);
  bool complete = Wire.read();
  return complete;
}

void transmitThumb(float value) {
  Wire.beginTransmission(1);

  float copy = value;
  byte* byteArray = (byte*) &copy;

  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  Wire.endTransmission();
}

bool MCPDone() {
  Wire.requestFrom(2, 1);
  bool complete = Wire.read();
  return complete;
}

void transmitMCP(float value) {
  Wire.beginTransmission(2);

  float copy = value;
  byte* byteArray = (byte*) &copy;

  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  Wire.endTransmission();
}

bool PIPDone() {
  Wire.requestFrom(3, 1);
  bool complete = Wire.read();
  return complete;
}

void transmitPIP(float value) {
  Wire.beginTransmission(3);

  float copy = value;
  byte* byteArray = (byte*) &copy;

  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  Wire.endTransmission();
}

bool DIPDone() {
  Wire.requestFrom(4, 1);
  bool complete = Wire.read();
  return complete;
}

void transmitDIP(float value) {
  Wire.beginTransmission(4);

  float copy = value;
  byte* byteArray = (byte*) &copy;

  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }
  // Serial.println(copy);

  Wire.endTransmission();
}

void loop() {
  // switch(currentState) {
  //   case CONTRACT:
  //     transmitMCP(1.00);
  //     transmitPIP(1.00);
  //     transmitDIP(1.00);
  //     delay(5);

  //     if (MCPDone() && PIPDone() && DIPDone()) {
  //       delay(1000);
  //       currentState = EXTEND;
  //     }
  //     break;
  //   default:
  //     transmitMCP(0);
  //     transmitPIP(0);
  //     transmitDIP(0);
  //     delay(5);

  //     if (MCPDone() && PIPDone() && DIPDone()) {
  //       delay(1000);
  //       currentState = CONTRACT;
  //     }
  //     break;
  // }

  switch(currentState) {
    case CONTRACT_FINGERS:
      transmitMCP(1.00);
      transmitPIP(1.00);
      transmitDIP(1.00);
      transmitThumb(0);

      delay(400);
      currentState = CONTRACT_THUMB;
      break;
    case CONTRACT_THUMB:
      transmitMCP(1.00);
      transmitPIP(1.00);
      transmitDIP(1.00);
      transmitThumb(1.00);
      delay(5);

      if (MCPDone() && PIPDone() && PIPDone() && ThumbDone()) {
        delay(1000);
        currentState = EXTEND_THUMB;
      }
      break;
    case EXTEND_THUMB:
      transmitMCP(1.00);
      transmitPIP(1.00);
      transmitDIP(1.00);
      transmitThumb(0);
      delay(100);

      currentState = EXTEND_FINGERS;
      break;
    default:
      transmitMCP(0);
      transmitPIP(0);
      transmitDIP(0);
      transmitThumb(0);

      if (MCPDone() && PIPDone() && DIPDone() && ThumbDone()) {
        delay(1000);
        currentState = CONTRACT_FINGERS;
      }
      break;
  }
}
