#include <ros.h>
#include <std_msgs/Float32.h>
#include <Wire.h>
#include "ros_setup.h"

extern volatile float MCP1;
extern volatile float MCP2;
extern volatile float MCP3;
extern volatile float MCP4;

ros::NodeHandle nh;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  nh.initNode();
  ROS_Setup(nh);
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
  transmitMCP(MCP1, MCP2, MCP3, MCP4);

  nh.spinOnce();
}
