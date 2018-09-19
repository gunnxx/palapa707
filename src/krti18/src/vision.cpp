#include <thread>

#include "ObjectDetector.h"
#include "ThreadSafe.h"

#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include "krti18/Shape.h"

// "Orange" color HSV parameter
int lH = 0;
int hH = 100;
int lS = 0;
int hS = 100;
int lV = 0;
int hV = 100;

// Flag of what things should be detected
int cv_flag;
void cv_flag_callback (const std_msgs::Int8& flag);

// Thread callback for capturing image
bool close_thread = false;
void cap_read (cv::VideoCapture &cap, ThreadSafe<cv::Mat> &image){
	std::cout << "Thread is spawned!\n";
	while(!close_thread) cap.read(image.access_data());
	std::cout << "Thread is closed!\n";
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "vision");
	ros::NodeHandle nh;

	cv::VideoCapture cap(0);
	ThreadSafe<cv::Mat> image;

	vision::ObjectDetector detector;

	ros::Publisher  cv_target_publisher = nh.advertise<krti18::Shape>("cv_target", 1);
	ros::Subscriber cv_flag_subscriber  = nh.subscribe("cv_flag", 1, cv_flag_callback);

	// First read to prevent empty cv::Mat (thread takes time to init)
	cap.read(image.access_data());
	std::thread video_reader(cap_read, std::ref(cap), std::ref(image));

	ros::Rate rate(20);		// 20 Hz
	ROS_INFO("Starting vision");

	while (ros::ok()) {
		ros::spinOnce();

		cv::Vec3f shape;
		krti18::Shape target;

		cv::Mat src = image.get_data();

		/*
		-1 ==> BREAK THE LOOP (EFFECT OF fm_changer.cpp ONLY)
		 1 ==> DROP LOG (LINGKARAN KUNING)
		 2 ==> PICK MP  (KOTAK HIJAU, LINGKARAN HIJAU)
		 3 ==> MP       (MOMOGI OREN)
		 4 ==> DROP MP  (KOTAK HIJAU, KOTAK OREN)
		 else ==> DETECT NOTHING
		*/
		if (cv_flag == -1 ) {
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

		cv_target_publisher.publish(target);
		rate.sleep();
		
	} // end of while(ros::ok())
	
	close_thread = true;
	video_reader.join();
	ROS_INFO("Vision is shutting down!");
	
	return 0;
}

void cv_flag_callback (const std_msgs::Int8& flag) {
	cv_flag = flag.data;
}
