#include "ros/ros.h"

#include "std_msgs/Int8.h"
#include "std_msgs/Int32.h"
#include "krti18/Shape.h"
#include "mavros_msgs/RCIn.h"

int count_validate = 0;
void cv_target_callback (const krti18::Shape& data);

// Channel 7 as GUIDED mode trigger (see fm_changer.cpp for details)
int OFFSET     = 300;
int RC_IN_CH7;
int RC_CH7_OFF = 900 + OFFSET;
int RC_CH7_ON  = 2000 - OFFSET;
void rc_in_callback (const mavros_msgs::RCIn& data);

// Mission type as to what movement to execute
int mission_type;
void mission_type_callback (const krti18::Mission& data);

int main(int argc, char **argv) {
	ros::init(argc, argv, "vision_threshold_checker");
	ros::NodeHandle nh;

	ros::Publisher cv_flag_publisher 	 	= nh.advertise<std_msgs::Int8>("cv_flag", 10);
	ros::Publisher count_validate_publisher = nh.advertise<std_msgs::Int32>("count_validate", 1);

	ros::Subscriber cv_target_subscriber 	= nh.subscribe("cv_target", 1, cv_target_callback);
	ros::Subscriber rc_in_subscriber 		= nh.subscribe("/mavros/rc/in", 1, rc_in_callback);
	ros::Subscriber mission_type_subscriber = nh.subscribe("mission_type", 1, mission_type_callback);

	ROS_INFO("vision_threshold_checker is waiting for Ch-7");
	// Initial conditions need to be fulfilled (ch7 should ON)
	while( !(ros::ok() &&
			 RC_IN_CH7 > RC_CH7_OFF)) ros::spinOnce();

	std_msgs::Int8 cv_flag;
	cv_flag.data = 2;
	cv_flag_publisher.publish(cv_flag);

	ros::Rate rate(20);		// 20 Hz
	ROS_INFO("Starting vision_threshold_checker!");

	while(ros::ok()){
		ros::spinOnce();

		if(mission_type == -1) break;
		
		std_msgs::Int32 count;
		count.data = count_validate;
		count_validate_publisher.publish(count);

		rate.sleep();
	}

	ROS_INFO("vision_threshold_checker is shutting down!");

	return 0;
}

void cv_target_callback (const krti18::Shape& data) {
	// If object detected
	if (data.r_obj != 0) count_validate += 1;
	else count_validate = std::max(0, count_validate - 2);
}

void rc_in_callback (const mavros_msgs::RCIn& data) {
	RC_IN_CH7 = data.channels[6];
}

void mission_type_callback (const krti18::Mission& data) {
	mission_type = data.mission_type;
}