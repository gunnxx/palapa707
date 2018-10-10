#include "Copter.h"
#include "ros/ros.h"
#include "mavros_msgs/RCIn.h"

// Channel 7 as GUIDED mode trigger (see fm_changer.cpp for details)
int OFFSET     = 300;
int RC_IN_CH7;
int RC_CH7_OFF = 900 + OFFSET;
int RC_CH7_ON  = 2000 - OFFSET;
void rc_in_callback (const mavros_msgs::RCIn& data);

int main (int argc, char **argv) {
	ros::init(argc, argv, "servo_test");
	ros::NodeHandle nh;

	UAV::Copter palapa707;

	ros::Subscriber rc_in_subscriber = nh.subscribe("/mavros/rc/in", 1, rc_in_callback);

	ROS_INFO("servo_test is wwaiting for Ch-7");
	// Initial conditions need to be fulfilled (ch7 should ON)
	while( !(ros::ok() &&
			 RC_IN_CH7 > RC_CH7_OFF)) ros::spinOnce();
	ROS_INFO("servo_test takes the MP");

	palapa707.get();

	ROS_INFO("servo_test is waiting for Ch-7");
	// Initial conditions need to be fulfilled (ch7 should ON)
	while( !(ros::ok() &&
			 RC_IN_CH7 < RC_CH7_ON)) ros::spinOnce();
	
	palapa707.drop();
	ROS_INFO("servo_test drops the MP");
	
	return 0;
}

void rc_in_callback (const mavros_msgs::RCIn& data) {
	RC_IN_CH7 = data.channels[6];
}
