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
# ==========
# Main Nodes
# ==========
add_executable(fm_changer
	src/fm_changer.cpp)
add_dependencies(fm_changer
	krti18_generate_messages_cpp)
target_link_libraries(fm_changer
	${catkin_LIBRARIES})

add_executable(main
	src/main.cpp)
add_dependencies(main
	krti18_generate_messages_cpp)
target_link_libraries(main
	${catkin_LIBRARIES})

add_executable(mission_control
	src/mission_control.cpp
	${CLASS_DEF})
add_dependencies(mission_control
	krti18_generate_messages_cpp)
target_link_libraries(mission_control
	${catkin_LIBRARIES}
	${OpenCV_LIBRARIES})

add_executable(vision
	src/vision.cpp
	${CLASS_DEF})
add_dependencies(vision
	krti18_generate_messages_cpp)
target_link_libraries(vision
	${catkin_LIBRARIES}
	${OpenCV_LIBRARIES})

# ==========
# Test Nodes
# ==========
add_executable(vision_test
	src/test/vision_test.cpp
	${CLASS_DEF})
add_dependencies(vision_test
	krti18_generate_messages_cpp)
target_link_libraries(vision_test
	${catkin_LIBRARIES}
	${OpenCV_LIBRARIES})

add_executable(vision_threshold_checker
	src/test/vision_threshold_checker.cpp)
add_dependencies(vision_threshold_checker
	krti18_generate_messages_cpp)
target_link_libraries(vision_threshold_checker
	${catkin_LIBRARIES})

add_executable(mission_control_test
	src/test/mission_control_test.cpp
	${CLASS_DEF})
add_dependencies(mission_control_test
	krti18_generate_messages_cpp)
target_link_libraries(mission_control_test
	${catkin_LIBRARIES}
	${OpenCV_LIBRARIES})

add_executable(record_video
	src/test/record_video.cpp)
add_dependencies(record_video
	krti18_generate_messages_cpp)
target_link_libraries(record_video
	${catkin_LIBRARIES}
	${OpenCV_LIBRARIES})

add_executable(servo_test
	src/test/servo_test.cpp
	${CLASS_DEF})
add_dependencies(servo_test
	krti18_generate_messages_cpp)
target_link_libraries(servo_test
	${catkin_LIBRARIES}
	${OpenCV_LIBRARIES})
	
add_executable(fm_changer_test
	src/test/fm_changer_test.cpp)
add_dependencies(fm_changer_test
	krti18_generate_messages_cpp)
target_link_libraries(fm_changer_test
	${catkin_LIBRARIES})

add_executable(waypoint_reached
	src/test/waypoint_reached.cpp)
add_dependencies(waypoint_reached
	krti18_generate_messages_cpp)
target_link_libraries(waypoint_reached
	${catkin_LIBRARIES})

add_executable(vision_test_no_thread
	src/test/vision_test_no_thread.cpp
	${CLASS_DEF})
add_dependencies(vision_test_no_thread
	krti18_generate_messages_cpp)
target_link_libraries(vision_test_no_thread
	${catkin_LIBRARIES}
	${OpenCV_LIBRARIES})