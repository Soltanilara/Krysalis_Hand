#include <ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <Wire.h>
// #include "ros_setup.h"

volatile float jointArray[3] = {0};

ros::NodeHandle nh;

void messageCb(const std_msgs::Float32MultiArray& msg) {
  for (int i = 0; i < 3; i++) {
    jointArray[i] = msg.data[i];
  }
}

ros::Subscriber<std_msgs::Float32MultiArray> sub("joints", &messageCb);

void setup() {
  Serial.begin(9600);
  Wire.begin();

  nh.initNode();
  nh.subscribe(sub);
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
  transmitMCP(jointArray[0], 0, 0, 0);
  transmitPIP(jointArray[1], 0, 0, 0);
  transmitDIP(jointArray[2], 0, 0, 0);

  nh.spinOnce();
}
