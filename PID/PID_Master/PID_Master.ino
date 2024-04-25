#include <Wire.h>
// #include "I2C.h"

enum state {
  CONTRACT,
  EXTEND
};

state currentState = CONTRACT;

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void transmitThumb(float CMC, float MCP, float IP) {
  Wire.beginTransmission(1);

  float copy = CMC;
  byte* byteArray = (byte*) &copy;

  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  copy = MCP;
  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  copy = IP;
  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  Wire.endTransmission();
}

void transmitMCP(float m1, float m2, float m3, float m4) {
  Wire.beginTransmission(2);

  float copy = m1;
  byte* byteArray = (byte*) &copy;

  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  copy = m2;
  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  copy = m3;
  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  copy = m4;
  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  Wire.endTransmission();
}

void transmitPIP(float p1, float p2, float p3, float p4) {
  Wire.beginTransmission(3);

  float copy = p1;
  byte* byteArray = (byte*) &copy;

  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  copy = p2;
  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  copy = p3;
  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  copy = p4;
  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  Wire.endTransmission();
}

void transmitDIP(float d1, float d2, float d3, float d4) {
  Wire.beginTransmission(4);

  float copy = d1;
  byte* byteArray = (byte*) &copy;

  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  copy = d2;
  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  copy = d3;
  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  copy = d4;
  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  Wire.endTransmission();
}

void loop() {
  //Individual control
  // transmitMCP(1, 0, 0, 0);

  //Close half
  // transmitMCP(1, 0, 1, 0);
  // transmitPIP(0, 1, 0, 1);
  // transmitDIP(1, 0, 1, 0);

  //Close all
  // transmitMCP(1, 1, 1, 1);
  // transmitPIP(1, 1, 1, 1);
  // transmitDIP(1, 1, 1, 1);

  //Open all
  transmitMCP(0, 0, 0, 0);
  transmitPIP(0, 0, 0, 0);
  transmitDIP(0, 0, 0, 0);
}
