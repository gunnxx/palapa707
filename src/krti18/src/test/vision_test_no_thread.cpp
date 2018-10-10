#include "ObjectDetector.h"

#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include "krti18/Shape.h"
#include "mavros_msgs/RCIn.h"

// "Orange" color HSV parameter
int lH = 80;
int hH = 140;
int lS = 30;
int hS = 255;
int lV = 235;
int hV = 255;

// Flag of what things should be detected
int cv_flag;
void cv_flag_callback (const std_msgs::Int8& flag);

// Channel 7 as GUIDED mode trigger (see fm_changer.cpp for details)
int OFFSET     = 300;
int RC_IN_CH7;
int RC_CH7_OFF = 900 + OFFSET;
int RC_CH7_ON  = 2000 - OFFSET;
void rc_in_callback (const mavros_msgs::RCIn& data);

int main(int argc, char **argv) {
	ros::init(argc, argv, "vision_test_no_thread");
	ros::NodeHandle nh;

	cv::VideoCapture cap(0);
	vision::ObjectDetector detector;

	cv::Mat src;
	cv::Vec3f shape;

	ros::Publisher  cv_target_publisher = nh.advertise<krti18::Shape>("cv_target", 1);
	ros::Subscriber cv_flag_subscriber  = nh.subscribe("cv_flag", 1, cv_flag_callback);
	ros::Subscriber rc_in_subscriber 	= nh.subscribe("/mavros/rc/in", 1, rc_in_callback);

	cv::namedWindow("Detection", cv::WINDOW_NORMAL);

	ros::Rate rate(20);
	ROS_INFO("Starting vision_test_no_thread!");

	while(ros::ok()){
		ros::spinOnce();

		bool success = cap.read(src);
		if(!success) break;

		krti18::Shape target;

		if (cv_flag == -1 || RC_IN_CH7 < RC_CH7_ON) {
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
		cv::imshow("Detection", src);

		cv_target_publisher.publish(target);
		rate.sleep();
	}

	return 0;
}

void cv_flag_callback (const std_msgs::Int8& flag) {
	cv_flag = flag.data;
}

void rc_in_callback (const mavros_msgs::RCIn& data) {
	RC_IN_CH7 = data.channels[6];
}