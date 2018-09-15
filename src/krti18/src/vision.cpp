#include <vector>

#include "ObjectDetector.h"

#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include "krti18/Shape.h"

// Flag of what things should be detected
int cv_flag;
void cv_flag_callback (const std_msgs::Int8& flag);

int main(int argc, char **argv) {
	ros::init(argc, argv, "vision");
	ros::NodeHandle nh;

	cv::VideoCapture cap(0);

	vision::ObjectDetector detector;
	cv::Vec3f square;
	cv::Vec3f circle;

	ros::Publisher  cv_target_publisher = nh.advertise<krti18::Shape>("cv_target", 1);
	ros::Subscriber cv_flag_subscriber  = nh.subscribe("cv_flag", 1, cv_flag_callback);

	while (ros::ok()) {
		ros::spinOnce();

		cv::Mat image;
		cap.read(image);
		krti18::Shape target;

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
			detector.findCircles(image, circle);
			
			target.x_obj = static_cast<int>(circle[0]);
			target.y_obj = static_cast<int>(circle[1]);
			target.r_obj = static_cast<int>(circle[2]);
		} else if (cv_flag == 2) {
			detector.findSquares(image, square);

			target.x_obj = static_cast<int>(square[0]);
			target.y_obj = static_cast<int>(square[1]);
			target.r_obj = static_cast<int>(square[2]);
		} else if (cv_flag == 3) {
			detector.findCircles(image, circle);
			
			target.x_obj = static_cast<int>(circle[0]);
			target.y_obj = static_cast<int>(circle[1]);
			target.r_obj = static_cast<int>(circle[2]);
		} else if (cv_flag == 4) {
			detector.findSquares(image, square);

			target.x_obj = static_cast<int>(square[0]);
			target.y_obj = static_cast<int>(square[1]);
			target.r_obj = static_cast<int>(square[2]);
		} else { /* Publish nothing */
			target.x_obj = 0;
			target.y_obj = 0;
			target.r_obj = 0;
		}

		cv_target_publisher.publish(target);
		
	} // end of while(ros::ok())
	
	ROS_INFO("Vision is shutting down!");
	
	return 0;
}

void cv_flag_callback (const std_msgs::Int8& flag) {
	cv_flag = flag.data;
}
