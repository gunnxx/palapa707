#include "ros/ros.h"
#include "Copter.h"
#include "mavros_msgs/RCIn.h"
#include "mavros_msgs/SetMode.h"
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
float height_desired   = 200.;

int main (int argc, char **argv)
{
	ros::init(argc, argv, "mission_control_test");
	ros::NodeHandle nh;

	UAV::Copter palapa707;

	ros::Publisher copter_state_publisher = nh.advertise<krti18::State>("copter_state", 1);

	ros::Subscriber mission_type_subscriber = nh.subscribe("mission_type", 1, mission_type_callback);
	ros::Subscriber rc_in_subscriber		= nh.subscribe("/mavros/rc/in", 1, rc_in_callback);

	ros::ServiceClient set_mode_client = nh.serviceClient<mavros_msgs::SetMode>("/mavros/set_mode");

	krti18::State state;
	mavros_msgs::SetMode flight_mode;
	flight_mode.request.base_mode = 0;

	ROS_INFO("mission_control_test is waiting for Ch-7");
	// Initial conditions need to be fulfilled (ch7 should ON)
	while( !(ros::ok() &&
			 RC_IN_CH7 > RC_CH7_OFF)) ros::spinOnce();

	ros::Rate rate(20);		// 20 Hz
	ROS_INFO("Starting mission_control_test!");

	while(ros::ok()){
		ros::spinOnce();
		/*
		-1 ==> BREAK
		 2 ==> CENTER
		 3 ==> HEIGHT
		*/
		if (mission_type == -1) break;
		
		else if (mission_type == 1) {
			state.doing_mission = true;
			copter_state_publisher.publish(state);

			flight_mode.request.custom_mode = "GUIDED";
			if (set_mode_client.call(flight_mode)) ROS_INFO("Flight mode changed to GUIDED");
			else ROS_INFO("WARNING : Failed to change flight mode to GUIDED");

			palapa707.go_center();

			flight_mode.request.custom_mode = "LOITER";
			if (set_mode_client.call(flight_mode)) ROS_INFO("Flight mode changed to AUTO");
			else ROS_INFO("WARNING : Failed to change flight mode to AUTO");

			state.doing_mission = false;
			copter_state_publisher.publish(state);

			// Sleep to wait main.cpp change the value of mission_type
			usleep(200);
		}

		else if (mission_type == 2) {
			state.doing_mission = true;
			copter_state_publisher.publish(state);

			flight_mode.request.custom_mode = "GUIDED";
			if (set_mode_client.call(flight_mode)) ROS_INFO("Flight mode changed to GUIDED");
			else ROS_INFO("WARNING : Failed to change flight mode to GUIDED");
			
			palapa707.change_height(height_desired);

			flight_mode.request.custom_mode = "LOITER";
			if (set_mode_client.call(flight_mode)) ROS_INFO("Flight mode changed to LOITER");
			else ROS_INFO("WARNING : Failed to change flight mode to LOITER");

			state.doing_mission = false;
			copter_state_publisher.publish(state);

			// Sleep to wait main.cpp change the value of mission_type
			usleep(200);
		}

		else if (mission_type == 3) {
			state.doing_mission = true;
			copter_state_publisher.publish(state);

			flight_mode.request.custom_mode = "GUIDED";
			if (set_mode_client.call(flight_mode)) ROS_INFO("Flight mode changed to GUIDED");
			else ROS_INFO("WARNING : Failed to change flight mode to GUIDED");

			palapa707.drop();

			flight_mode.request.custom_mode = "LOITER";
			if (set_mode_client.call(flight_mode)) ROS_INFO("Flight mode changed to LOITER");
			else ROS_INFO("WARNING : Failed to change flight mode to LOITER");

			state.doing_mission = false;
			copter_state_publisher.publish(state);

			// Sleep to wait main.cpp change the value of mission_type
			usleep(200);
		}

		else if (mission_type == 4) {
			state.doing_mission = true;
			copter_state_publisher.publish(state);

			flight_mode.request.custom_mode = "GUIDED";
			if (set_mode_client.call(flight_mode)) ROS_INFO("Flight mode changed to GUIDED");
			else ROS_INFO("WARNING : Failed to change flight mode to GUIDED");

			palapa707.get();

			flight_mode.request.custom_mode = "LOITER";
			if (set_mode_client.call(flight_mode)) ROS_INFO("Flight mode changed to LOITER");
			else ROS_INFO("WARNING : Failed to change flight mode to LOITER");

			state.doing_mission = false;
			copter_state_publisher.publish(state);

			// Sleep to wait main.cpp change the value of mission_type
			usleep(200);
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