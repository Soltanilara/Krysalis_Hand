cmake_minimum_required(VERSION 2.8.3)

project(P3_ROS)

find_package(catkin REQUIRED)

catkin_package()

find_package(roslaunch)

install(DIRECTORY launch DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  PATTERN "setup_assistant.launch" EXCLUDE)
install(DIRECTORY config DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
