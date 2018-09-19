#include <iostream>
#include "unistd.h"	// usleep(microseconds)

#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include "mavros_msgs/RCIn.h"
#include "krti18/Mission.h"
#include "krti18/Shape.h"
#include "krti18/State.h"

// To validate object detection (act like timer)
int count_validate = 0;
const int validation_thresh = 40;

// Mission status
bool is_doing_mission;

int CV_FLAGS[]  = {2, 3, 4, 5};    // cv mode sequence (read below for mode details)
int MISSIONS[]  = {2, 3, 1, 1};	 // mission_type sequence (read below for mode details)
// PS : the last cv_mode and mission_type is required to avoid segmentation fault

// Channel 7 as GUIDED mode trigger (see fm_changer.cpp for details)
int OFFSET     = 300;
int RC_IN_CH7;
int RC_CH7_OFF = 900 + OFFSET;
int RC_CH7_ON  = 2000 - OFFSET;

void cv_target_callback    (const krti18::Shape& data);
void rc_in_callback 	   (const mavros_msgs::RCIn& data);
void copter_state_callback (const krti18::State& data);

int main (int argc, char **argv) {
	ros::init(argc, argv, "main");
	ros::NodeHandle nh;

	/*
	PUBLISH std_msgs::Int8 TO vision.cpp
	-1 ==> BREAK THE LOOP (EFFECT OF fm_changer.cpp ONLY)
	 1 ==> DROP LOG (LINGKARAN KUNING)
	 2 ==> PICK MP  (KOTAK HIJAU, LINGKARAN HIJAU)
	 3 ==> MP       (MOMOGI OREN)
	 4 ==> DROP MP  (KOTAK HIJAU, KOTAK OREN)
	 else ==> DETECT NOTHING
	*/
	ros::Publisher cv_flag_publisher 	 	= nh.advertise<std_msgs::Int8>("cv_flag", 10);

	/*
	SENDING Mission.msg TO mission_switch.cpp
	-1 ==> BREAK THE LOOP (EFFECT OF fm_changer.cpp ONLY)
	 1 ==> DROP (GUIDED -> MISSION -> AUTO)
	 2 ==> GO DOWN FOR MP (GUIDED -> MISSION -> LOITER)
	 3 ==> PICK UP MP (GUIDED -> MISSION -> AUTO)
	 else ==> DO NOTHING
	**go down for mp and pivk up mp mission sequence is separated
	  becuase it uses different cv detection method**
	*/
	ros::Publisher mission_type_publisher = nh.advertise<krti18::Mission>("mission_type", 1);
	krti18::Mission mission;

	ros::Subscriber cv_target_subscriber 	= nh.subscribe("cv_target", 1, cv_target_callback);
	ros::Subscriber rc_in_subscriber 		= nh.subscribe("/mavros/rc/in", 1, rc_in_callback);
	ros::Subscriber copter_state_subscriber = nh.subscribe("copter_state", 1, copter_state_callback);

	// Initial conditions need to be fulfilled (ch7 should ON)
	while( !(ros::ok() &&
			 RC_IN_CH7 > RC_CH7_OFF)) ros::spinOnce();

	// Sleep for 20 seconds before turning on CV to prevent detecting landing pad
	ROS_INFO("Vision is waiting 20 seconds to prevent detecting landing pad.");
	usleep(20000000);
	ROS_INFO("Vision is ready!");

	// Initial cv_flag
	int index_mission = 0;
	int index_cv = 0;
	std_msgs::Int8 cv_flag;
	cv_flag.data = CV_FLAGS[index_cv];
	cv_flag_publisher.publish(cv_flag);

	while (ros::ok()) {
		ros::spinOnce();

		// If object is confirmed
		if (count_validate > validation_thresh) {
			ROS_INFO("Object is detected.\nExecuting its corresponding mission.\n");
			
			// Publishing mission_type
			mission.mission_type = MISSIONS[index_mission];
			mission_type_publisher.publish(mission);

			// Sleep to wait mission_switch.cpp change the state of
			// copter to is_doing_mission = true
			usleep(200);
			
			// Wait for the mission to done
			while(is_doing_mission) ros::spinOnce();

			// Clearing up value published to mission_switch.cpp
			// Other than (-1) or 1-3 means no mission (do nothing)
			mission.mission_type = 0;
			mission_type_publisher.publish(mission);

			// Change mission_type and cv_flag after mission is done
			index_mission++;
			index_cv++;

			cv_flag.data = CV_FLAGS[index_cv];
			cv_flag_publisher.publish(cv_flag);
			
			// Sleep for 5 seconds before reseting count_validate
			// It prevents detection of the same place
			usleep(5000000);
			count_validate = 0;
			
			ROS_INFO("Current mission is done.");
		}
		
	} // end of while(ros::ok())
	
	ROS_INFO("main is shutting down");
	
	return 0;
}

void cv_target_callback (const krti18::Shape& data) {
	// If object detected
	if (data.r_obj != 0) count_validate += 1;
	else count_validate = std::max(count_validate - 2, 0);
}

void rc_in_callback (const mavros_msgs::RCIn& data) {
	RC_IN_CH7 = data.channels[6];
}

void copter_state_callback (const krti18::State& data) {
	is_doing_mission = data.doing_mission;
}
