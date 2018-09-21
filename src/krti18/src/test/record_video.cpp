#include "ros/ros.h"

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "std_msgs/Int8.h"
#include "mavros_msgs/RCIn.h"

// Recorded video parameters
const int frame_width  = 640;
const int frame_height = 480;
const int fps = 30;

// Channel 7 as GUIDED mode trigger (see fm_changer.cpp for details)
int OFFSET     = 300;
int RC_IN_CH7;
int RC_CH7_OFF = 900 + OFFSET;
int RC_CH7_ON  = 2000 - OFFSET;
void rc_in_callback (const mavros_msgs::RCIn& data);

// Flag to close this recorder
int cv_flag;
void cv_flag_callback (const std_msgs::Int8& flag);

int main(int argc, char **argv) {
	ros::init(argc, argv, "record_video");
	ros::NodeHandle nh;

	cv::VideoCapture cap(0);
	cv::VideoWriter recorder("out.avi",
							 cv::VideoWriter::fourcc('M', 'J', 'P', 'G'),
							 fps,
							 cv::Size(frame_width, frame_height),
							 true);

	cap.set(cv::CAP_PROP_FPS, fps);
	cap.set(cv::CAP_PROP_FRAME_WIDTH, frame_width);
	cap.set(cv::CAP_PROP_FRAME_HEIGHT, frame_height);

	ros::Subscriber cv_flag_subscriber  = nh.subscribe("cv_flag", 1, cv_flag_callback);
	ros::Subscriber rc_in_subscriber = nh.subscribe("/mavros/rc/in", 1, rc_in_callback);

	ROS_INFO("record_video is waiting for Ch-7");
	// Initial conditions need to be fulfilled (ch7 should ON)
	while( !(ros::ok() &&
			 RC_IN_CH7 > RC_CH7_OFF)) ros::spinOnce();

	ros::Rate rate(60);		// 60 Hz
	ROS_INFO("Starting record_video!");
	
	while(ros::ok()){
		ros::spinOnce();

		if(cv_flag == -1) break;

		cv::Mat src;
		cap.read(src);
		recorder.write(src);

		rate.sleep();
	}

	ROS_INFO("record_video is shutting down!");

	return 0;
}

void cv_flag_callback (const std_msgs::Int8& flag) {
	cv_flag = flag.data;
}

void rc_in_callback (const mavros_msgs::RCIn& data) {
	RC_IN_CH7 = data.channels[6];
}