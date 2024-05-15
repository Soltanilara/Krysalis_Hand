#ifndef ROS_SETUP_H
#define ROS_SETUP_H
#include <ros.h>
#include <std_msgs/Float32.h>

volatile float MCP1 = 0;
volatile float MCP2 = 0;
volatile float MCP3 = 0;
volatile float MCP4 = 0;

void MCP1_Cb(const std_msgs::Float32& MCP1_msg) {
  MCP1 = MCP1_msg.data;
}

void MCP2_Cb(const std_msgs::Float32& MCP2_msg) {
  MCP2 = MCP2_msg.data;
}

void MCP3_Cb(const std_msgs::Float32& MCP3_msg) {
  MCP3 = MCP3_msg.data;
}

void MCP4_Cb(const std_msgs::Float32& MCP4_msg) {
  MCP4 = MCP4_msg.data;
}

ros::Subscriber<std_msgs::Float32> sub_MCP1("MCP1", &MCP1_Cb);
ros::Subscriber<std_msgs::Float32> sub_MCP2("MCP2", &MCP2_Cb);
ros::Subscriber<std_msgs::Float32> sub_MCP3("MCP3", &MCP3_Cb);
ros::Subscriber<std_msgs::Float32> sub_MCP4("MCP4", &MCP4_Cb);

void ROS_Setup(ros::NodeHandle nh) {
  nh.subscribe(sub_MCP1);
  nh.subscribe(sub_MCP2);
  nh.subscribe(sub_MCP3);
  nh.subscribe(sub_MCP4);
}
#endif