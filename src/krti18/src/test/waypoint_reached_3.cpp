#include "ros/ros.h"
#include "Copter.h"
#include "krti18/Mission.h"
#include "mavros_msgs/WaypointReached.h"

// Indicating Reached Waypoint and Mission
int waypoint_reached = 0;
bool mission_1_reached = false;
bool mission_2_reached = false;
bool mission_3_reached = false;
bool mission_4_reached = false;
void mission_reached_callback(const mavros_msgs::WaypointReached& data);

int main(int argc, char **argv){
	ros::init(argc, argv, "waypoint_reached");
	ros::NodeHandle nh;

	UAV::Copter palapa707;
	
	ros::Publisher  mission_type_publisher     = nh.advertise<krti18::Mission>("mission_type", 1);
	ros::Subscriber mission_reached_subscriber = nh.subscribe("/mavros/mission/reached", 1, mission_reached_callback);

	ros::Rate rate(30);
	ROS_INFO("Starting waypoint_reached!");
	
	while(ros::ok()){
		ros::spinOnce();
		
		if(waypoint_reached == 3 && !mission_1_reached){
			krti18::Mission data;
			data.mission_type = 1;
			mission_type_publisher.publish(data);
			
			mission_1_reached = true;
		}
		
		if(waypoint_reached == 7 && !mission_2_reached){
			krti18::Mission data;
			data.mission_type = 2;
			mission_type_publisher.publish(data);
			
			mission_2_reached = true;
		}
		
		if(waypoint_reached == 9 && !mission_3_reached){
			krti18::Mission data;
			data.mission_type = 1;
			mission_type_publisher.publish(data);
			
			mission_3_reached = true;
		}
		
		if(waypoint_reached == 11 && !mission_4_reached){
			krti18::Mission data;
			data.mission_type = 2;
			mission_type_publisher.publish(data);
			
			mission_4_reached = true;
		}

		if(mission_1_reached &&
		   mission_2_reached &&
		   mission_3_reached &&
		   mission_4_reached) break;

		rate.sleep();
	}

	ROS_INFO("waypoint_reached is shutting down!");
	ROS_INFO("Check the WaypointReached.wp_seq when all waypoint is done");

	return 0;
}

void mission_reached_callback(const mavros_msgs::WaypointReached& data){
	waypoint_reached = data.wp_seq;
}
