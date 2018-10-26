#include <iostream>
#include "ObjectDetector.h"

#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include "krti18/Shape.h"

// "Orange" color HSV parameter
int lH = 90;
int hH = 120;
int lS = 90;
int hS = 180;
int lV = 200;
int hV = 255;

// Flag of what things should be detected
int cv_flag;
void cv_flag_callback (const std_msgs::Int8& flag);

int main(int argc, char **argv) {
	ros::init(argc, argv, "vision_test_no_thread");
	ros::NodeHandle nh;

	cv::VideoCapture cap(0);
	cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
	cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
	cap.set(cv::CAP_PROP_FPS, 30);
	
	vision::ObjectDetector detector;

	cv::Mat src;

	ros::Publisher  cv_target_publisher = nh.advertise<krti18::Shape>("cv_target", 1);
	ros::Subscriber cv_flag_subscriber  = nh.subscribe("cv_flag", 1, cv_flag_callback);

	ros::Rate rate(20);
	ROS_INFO("Starting vision_test_no_thread!");

	while(ros::ok()){
		ros::spinOnce();

		bool success = cap.read(src);
		if(!success) break;

		cv::Vec3f shape;
		krti18::Shape target;

		if (cv_flag == -1) {
			break;
		} else if (cv_flag == 1) {
			detector.findCircle(src, shape);
			
			target.x_obj = static_cast<int>(shape[0]);
			target.y_obj = static_cast<int>(shape[1]);
			target.r_obj = static_cast<int>(shape[2]);
		} else if (cv_flag == 2) {
			detector.findSquare(src, shape);

			target.x_obj = static_cast<int>(shape[0]);
			target.y_obj = static_cast<int>(shape[1]);
			target.r_obj = static_cast<int>(shape[2]);
		} else if (cv_flag == 3) {
			detector.findColor(src, shape, lH, hH, lS, hS, lV, hV);
			
			target.x_obj = static_cast<int>(shape[0]);
			target.y_obj = static_cast<int>(shape[1]);
			target.r_obj = static_cast<int>(shape[2]);
		} else if (cv_flag == 4) {
			detector.findSquare(src, shape);

			target.x_obj = static_cast<int>(shape[0]);
			target.y_obj = static_cast<int>(shape[1]);
			target.r_obj = static_cast<int>(shape[2]);
		} else { /* Publish nothing */
			target.x_obj = 0;
			target.y_obj = 0;
			target.r_obj = 0;
		}

		detector.markColor(src, shape);
		
		cv_target_publisher.publish(target);
		rate.sleep();
	}

	return 0;
}

void cv_flag_callback (const std_msgs::Int8& flag) {
	cv_flag = flag.data;
}