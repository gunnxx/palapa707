# How To Run Tests

All tests are using Channel-7 as trigger. Run below command first and the node will wait for trigger.

### Calibrating `validation_threshold` :
Activate necessary nodes
```shell
roslaunch mavros apm.launch
rosrun krti18 fm_changer
rosrun krti18 vision_test
rosrun krti18 vision_threshold_checker
```
Observe the following data
```shell
rostopic echo /count_validate
rostopic echo /cv_target		# optional
```
> The default is detecting square i.e. `cv_flag = 2`. If you want to detect other things, change `cv_flag` value in `vision_threshold_checker.cpp`.

### Recording video for further observation i.e calibrating HSV or check detection robustness :
Activate necessary nodes
```shell
roslaunch mavros apm.launch
rosrun krti18 fm_changer
rosrun krti18 record_video
```
> The default is (width, height, fps) = (640, 480, 30). Adjust the parameters `frame_width`, `frame_height`, and `fps` in `record_video.cpp` according to your camera spec and your desired performance.

### Testing `UAV::Copter::change_height(float desired_alt)` :
Activate necesary nodes
```shell
roslaunch mavros apm.launch
rosrun krti18 fm_changer
rosrun krti18 mission_control_test
rostopic pub /mission_type krti18/Mission "mission_type : 2"
```
Observe the following data
```shell
# Subtract with desired_alt = error_z
rostopic echo /lidar_alt

# Check vz
rostopic echo /mavros/global_position/gp_vel
```
> The default desired altitude is 200 cm. If you  want to change the desired altitude, change `height_desired` value in `mission_control_test.cpp`.

### Testing `UAV::Copter::go_center()` :
Activate necessary nodes
```shell
roslaunch mavros apm.launch
rosrun krti18 fm_changer
rosrun krti18 vision_test
rosrun krti18 mission_control_test
rostopic pub /mission_type krti18/Mission "mission_type : 1"
```
Observe the following data
```shell
# Subtract with _X_CAM and _Y_CAM to get error_x and error_y
rostopic echo /cv_target

# Check vx and vy
rostopic echo /mavros/global_position/gp_vel
```
> The default setpoints are `_X_CAM = 320` and `_Y_CAM = 240`. If you want to change the setpoints, change `_X_CAM` and `_Y_CAM` values in `include/Copter.h` according to your camera position in Copter and the resolution of your camera.

### Testing `UAV::Copter::drop()` and `UAV::Copter::get()` :
Activate necessary nodes
```shell
roslaunch mavros apm.launch
rosrun krti18 fm_changer
rosrun krti18 mission_control_test

## Choose one
rostopic pub /mission_type krti18/Mission "mission_type : 3"	# drop()
rostopic pub /mission_type krti18/Mission "mission_type : 4"	# get()
```
> The default servo degrees are `_drop_servo_degree = 0` and `_get_servo_degree  = 120`. If you want to change the servo degrees, change `_get_servo_degree` and `_drop_servo_degree` values in `include/Copter.h` according to your desired servo configuration.

## Notes
Failsafe can be executed by turning off Channel-7. Turning off Channel-7 will change the flight mode to `LOITER` and all nodes will be closed.