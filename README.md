# Krysalis Hand

## Overview
Krysalis Hand is a five-finger robotic end-effector that combines a lightweight design, high payload capacity, and a high number of degrees of freedom (DoF) to enable dexterous manipulation in both industrial and research settings. 

The Krysalis repository holds all the code necessary to operate the *Krysalis Hand* and conduct *teleoperation* using the MANUS Meta Glove. It is recommended to use a Linux machine to run this code.

To learn more about the details of our robotic hand, check out our [paper](https://arxiv.org/abs/2504.12967).

<img src="image/hand.png" alt="Kysallis Hand">


## Modules:

### Hand-Codes

The Hand-Codes repository contains all of the firmware for all of the Arduinos. The master runs on a Raspberry Pi Pico, while the rest the modules (MCP, PIP, DIP, etc.) run on Arduino. The Arduino Codes in each of the folders is readily available, but the Raspberry Pi Pico code requires a few more steps before build.

### SDKClient_Linux

The MANUS SDK is used to pull real time fingertip data from the MANUS Glove to the ROS 2 Nodes which is then used to calculate the joint angles for teleoperation. For specific steps on downloading and running the SDK, check out the [SDKClient_Linux Readme](https://github.com/Soltanilara/Krysalis_Hand/tree/main/SDKClient_Linux)

This code is pulled from the LEAP Hand's [Bidex Manus Teleop](https://github.com/leap-hand/Bidex_Manus_Teleop) repository for teleoperating their hand using the MANUS Meta Gloves. It is similar to the MANUS [C++ SDK](https://docs.manus-meta.com/2.4.0/Plugins/SDK/) but adds [ZMQ bindings](https://github.com/zeromq/cppzmq/tree/master) to communicate with the ROS 2 package. 



### glove_ROS

In glove_ROS you can find the code used for teleoperation of the Krysalis Hand using a ROS2 workspace for communication and Pybullet for angle calculations. 

This code is also pulled from the LEAP Hand's [ROS 2 Library](https://github.com/leap-hand/Bidex_Manus_Teleop) for teleoperating their hand from using the MANUS Meta Gloves. We then repurposed the code to fit the dimensions of the Krysalis Hand. 

![](image/IMG_6141.mov)



