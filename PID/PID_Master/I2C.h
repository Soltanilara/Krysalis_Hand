#ifndef I2C_H
#define I2C_H
bool MCPDone() {
  Wire.requestFrom(2, 1);
  bool complete = Wire.read();
  return complete;
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

bool PIPDone() {
  Wire.requestFrom(3, 1);
  bool complete = Wire.read();
  return complete;
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

bool DIPDone() {
  Wire.requestFrom(4, 1);
  bool complete = Wire.read();
  return complete;
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
#endif