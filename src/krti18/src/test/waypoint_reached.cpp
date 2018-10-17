#include "ros/ros.h"
#include "Copter.h"
#include "mavros_msgs/WaypointReached.h"

int waypoint_reached;
bool mission_1_reached = false;	// Indicating already done
bool mission_2_reached = false;	// the mission for the particular waypoint
void mission_reached_callback(const mavros_msgs::WaypointReached& data);

int main(int argc, char **argv){
	ros::init(argc, argv, "waypoint_reached");
	ros::NodeHandle nh;

	UAV::Copter palapa707;

	ros::Subscriber mission_reached_subscriber = nh.subscribe("/mavros/mission/reached", 1, mission_reached_callback);

	ros::Rate rate(30);
	ROS_INFO("Starting waypoint_reached!");
	
	while(ros::ok()){
		ros::spinOnce();

		if(waypoint_reached == 2 && !mission_1_reached){
			palapa707.get();
			mission_1_reached = true;
		}

		else if(waypoint_reached == 4 && !mission_2_reached){
			palapa707.drop();
			mission_2_reached = true;
		}

		if(mission_1_reached && mission_2_reached) break;

		rate.sleep();
	}

	ROS_INFO("waypoint_reached is shutting down!");
	ROS_INFO("Check the WaypointReached.wp_seq when all waypoint is done");

	return 0;
}

void mission_reached_callback(const mavros_msgs::WaypointReached& data){
	waypoint_reached = data.wp_seq;
}