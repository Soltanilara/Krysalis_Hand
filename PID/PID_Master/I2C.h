#ifndef I2C_H
#define I2C_H
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
#endif