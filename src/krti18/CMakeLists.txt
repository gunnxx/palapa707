cmake_minimum_required(VERSION 2.8.3)
project(krti18)

## Using std c++11
add_compile_options(-std=c++11)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  mavros
  message_generation
  roslaunch
)

## Find OpenCV-3
find_package(OpenCV 3 REQUIRED)

## Check all *.launch files in launch directory
roslaunch_add_file_check(launch)

## Declare ROS messages and services
add_message_files(FILES
				  Ardu.msg
				  Mission.msg
				  Shape.msg
				  State.msg)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package(CATKIN_DEPENDS message_runtime)

## Add include directories to the build
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

## Add class definition
set(CLASS_DEF
	src/ObjectDetector.cpp
	src/Copter.cpp)

## Add executable files
add_executable(fm_changer
	src/fm_changer.cpp)
target_link_libraries(fm_changer
	${catkin_LIBRARIES})

add_executable(main
	src/main.cpp)
target_link_libraries(main
	${catkin_LIBRARIES})

add_executable(mission_control
	src/mission_control.cpp
	${CLASS_DEF})
target_link_libraries(mission_control
	${catkin_LIBRARIES}
	${OpenCV_LIBRARIES})

add_executable(vision
	src/vision.cpp
	${CLASS_DEF})
target_link_libraries(vision
	${catkin_LIBRARIES}
	${OpenCV_LIBRARIES})
