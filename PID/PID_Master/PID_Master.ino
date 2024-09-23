#include <ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <Wire.h>

//Limits
#define THUMB_CMC 106.266
#define THUMB_MCP 52.73
#define THUMB_IP 45

#define MCP_INDEX 103.14
#define PIP_INDEX 75.08
#define DIP_INDEX 68.1

#define MCP_MIDDLE 101.93
#define PIP_MIDDLE 73.47
#define DIP_MIDDLE 73.05

#define MCP_RING 100.57
#define PIP_RING 72.93
#define DIP_RING 73.58

#define MCP_PINKY 98.94
#define PIP_PINKY 72.04
#define DIP_PINKY 72.06

// volatile float jointArray[3] = {0};

// ros::NodeHandle nh;

// void messageCb(const std_msgs::Float32MultiArray& msg) {
//   for (int i = 0; i < 3; i++) {
//     jointArray[i] = msg.data[i];
//   }
// }

// ros::Subscriber<std_msgs::Float32MultiArray> sub("joints", &messageCb);

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // nh.initNode();
  // nh.subscribe(sub);
}

void normalize(float& value, float limit) {
  if (value > limit) {
    value = limit;
  }
  else if (value < 0) {
    value = 0;
  }
}

void transmitThumb(float CMC, float MCP, float IP) {
  normalize(CMC, THUMB_CMC);
  normalize(MCP, THUMB_MCP);
  normalize(IP, THUMB_IP);

  Wire.beginTransmission(1);

  float copy = CMC / THUMB_CMC;
  byte* byteArray = (byte*) &copy;

  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  copy = MCP / THUMB_MCP;
  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  copy = IP / THUMB_IP;
  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  Wire.endTransmission();
}

void transmitMCP(float m1, float m2, float m3, float m4) {
  normalize(m1, MCP_INDEX);
  normalize(m2, MCP_MIDDLE);
  normalize(m3, MCP_RING);
  normalize(m4, MCP_PINKY);
  
  Wire.beginTransmission(2);

  float copy = m1 / MCP_INDEX;
  byte* byteArray = (byte*) &copy;

  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  copy = m2 / MCP_MIDDLE;
  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  copy = m3 / MCP_RING;
  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  copy = m4 / MCP_PINKY;
  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  Wire.endTransmission();
}

void transmitPIP(float p1, float p2, float p3, float p4) {
  normalize(p1, PIP_INDEX);
  normalize(p2, PIP_MIDDLE);
  normalize(p3, PIP_RING);
  normalize(p4, PIP_PINKY);

  Wire.beginTransmission(3);

  float copy = p1 / PIP_INDEX;
  byte* byteArray = (byte*) &copy;

  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  copy = p2 / PIP_MIDDLE;
  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  copy = p3 / PIP_RING;
  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  copy = p4 / PIP_PINKY;
  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  Wire.endTransmission();
}

void transmitDIP(float d1, float d2, float d3, float d4) {
  normalize(d1, DIP_INDEX);
  normalize(d2, DIP_MIDDLE);
  normalize(d3, DIP_RING);
  normalize(d4, DIP_PINKY);

  Wire.beginTransmission(4);

  float copy = d1 / DIP_INDEX;
  byte* byteArray = (byte*) &copy;

  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  copy = d2 / DIP_MIDDLE;
  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  copy = d3 / DIP_RING;
  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  copy = d4 / DIP_PINKY;
  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }

  Wire.endTransmission();
}

void loop() {
  transmitMCP(0, 0, 0, 0);
  transmitPIP(0, 0, 0, 0);
  transmitDIP(0, 0, 0, 0);
  transmitThumb(0, 0, 0);

  // Index touching thumb
  // transmitMCP(103.14, 0, 0, 0);
  // transmitPIP(75.08, 0, 0, 0);
  // transmitDIP(0, 0, 0, 0);
  // transmitThumb(30, 52.73, 40);

  // Middle touching thumb
  // transmitMCP(0, 101.93, 0, 0);
  // transmitPIP(0, 73.47, 0, 0);
  // transmitDIP(0, 0, 0, 0);
  // transmitThumb(40, 52.73, 45);

  // Ring touching thumb
  // transmitMCP(0, 0, 85, 0);
  // transmitPIP(0, 0, 72.93, 0);
  // transmitDIP(0, 0, 0, 0);
  // transmitThumb(70, 52.73, 20);

  // Pinkie touching thumb
  // transmitMCP(0, 0, 0, 98.94);
  // transmitPIP(0, 0, 0, 60);
  // transmitDIP(0, 0, 0, 0);
  // transmitThumb(90, 0, 30);

  // nh.spinOnce();
}
