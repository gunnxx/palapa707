#include "ros/ros.h"
#include "mavros_msgs/WaypointReached.h"

int mission_reached;
void mission_reached_callback(const mavros_msgs::WaypointReached& data);

int main(int argc, char **argv){
	ros::init(argc, argv, "waypoint_reached");
	ros::NodeHandle nh;

	ros::Subscriber mission_reached_subscriber = nh.subscribe("/mavros/mission/reached", 1, mission_reached_callback);

	ros::Rate rate(30);
	
	while(ros::ok()){
		ros::spinOnce();

		ROS_INFO("WaypointReached.wp_seq = %d", mission_reached);
	}

	return 0;
}

void mission_reached_callback(const mavros_msgs::WaypointReached& data){
	mission_reached = data.wp_seq;
}