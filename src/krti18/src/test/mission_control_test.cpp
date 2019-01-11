#include "ros/ros.h"
#include "Copter.h"
#include "mavros_msgs/RCIn.h"
#include "krti18/Mission.h"

// Mission type as to what movement to execute
int mission_type;
void mission_type_callback (const krti18::Mission& data);

// Channel 7 as GUIDED mode trigger (see fm_changer.cpp for details)
int OFFSET     = 300;
int RC_IN_CH7;
int RC_CH7_OFF = 900 + OFFSET;
int RC_CH7_ON  = 2000 - OFFSET;
void rc_in_callback (const mavros_msgs::RCIn& data);

// Height reference in cm
float height_desired   = 145.;
float height_up 	   = 400.;

int main (int argc, char **argv) {
	ros::init(argc, argv, "mission_control_test");
	ros::NodeHandle nh;

	UAV::Copter palapa707;

	ros::Publisher copter_state_publisher = nh.advertise<krti18::State>("copter_state", 1);

	ros::Subscriber mission_type_subscriber = nh.subscribe("mission_type", 1, mission_type_callback);
	ros::Subscriber rc_in_subscriber		= nh.subscribe("/mavros/rc/in", 1, rc_in_callback);

	krti18::State state;
	ros::Rate rate(20);		// 20 Hz

	ROS_INFO("mission_control_test is waiting for Ch-7");
	while( !(ros::ok() && RC_IN_CH7 > RC_CH7_OFF)){
		ros::spinOnce();
		rate.sleep();
	}
	ROS_INFO("Starting mission_control_test!");

	while(ros::ok()){
		ros::spinOnce();
		/*
		-1 ==> BREAK
		 1 ==> CENTER
		 2 ==> HEIGHT
		 3 ==> PARTIAL-MISSION
		*/
		if (mission_type == -1) break;
		
		// Take Payload
		else if(mission_type == 1) {
			state.doing_mission = true;
			copter_state_publisher.publish(state);

			palapa707.change_flight_mode(std::string("GUIDED"));
			palapa707.go_center();
			palapa707.change_flight_mode(std::string("LOITER"));
			usleep(2000000);
			palapa707.change_flight_mode(std::string("GUIDED"));
			palapa707.go_down_and_centerize(165);
			palapa707.change_flight_mode(std::string("LOITER"));
			usleep(2000000);
			palapa707.change_flight_mode(std::string("GUIDED"));
			//palapa707.get();
			palapa707.go_up(400);
			palapa707.change_flight_mode(std::string("AUTO"));

			state.doing_mission = false;
			copter_state_publisher.publish(state);

			mission_type = 0;
		}
		
		// Drop Payload
		else if(mission_type == 2) {
			state.doing_mission = true;
			copter_state_publisher.publish(state);
			
			palapa707.change_flight_mode(std::string("GUIDED"));
			palapa707.go_down_and_centerize(170);
			palapa707.change_flight_mode(std::string("LOITER"));
			usleep(2000000);
			palapa707.change_flight_mode(std::string("GUIDED"));
			palapa707.drop();
			palapa707.go_up(400);
			palapa707.change_flight_mode(std::string("AUTO"));
			
			state.doing_mission = false;
			copter_state_publisher.publish(state);

			mission_type = 0;
		}

		rate.sleep();

	} // end of while(ros::ok())
	
	ROS_INFO("mission_control_test is shutting down!");
	
	return 0;
}

void mission_type_callback (const krti18::Mission& data) {
	mission_type = data.mission_type;
}

void rc_in_callback (const mavros_msgs::RCIn& data) {
	RC_IN_CH7 = data.channels[6];
}
