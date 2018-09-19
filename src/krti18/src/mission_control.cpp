#include "ros/ros.h"
#include "Copter.h"
#include "mavros_msgs/SetMode.h"
#include "krti18/Mission.h"

/* ===========================================================================
	MISSION_TYPE DETAILS :
	1 ==> DROP
	2 ==> GO DOWN FOR MP
	3 ==> PICK UP FOR MP

	GO DOWN and PICK UP for MP is separated to change object detection method
    from detecting square to detecting MP (circle / blob)
   =========================================================================== */
int mission_type;
void mission_type_callback (const krti18::Mission& data);

/*	=============================================
					COPTER HEIGHT

	height_up	------------------------------
													---------------+---------------
												          ___ /^^[___              _
												         /|^+----+   |#___________//
												       ( -+ |____|   _______-----+/
												        ==_________--'            \
												          ~_|___|__
	height_down	------------------------------

	height_drop	------------------------------

	height_mp	------------------------------
							====
							|MP|
							====
							 ++
							 ++
							 ++
							 ++
							 ==
							====
	============================================= */
float height_up   = 400.;
float height_down = 200.;
float height_drop = 170.;
float height_mp   = 150.;

int main (int argc, char **argv)
{
	ros::init(argc, argv, "mission_control");
	ros::NodeHandle nh;

	UAV::Copter palapa707;

	ros::Publisher copter_state_publisher = nh.advertise<krti18::State>("copter_state", 1);

	ros::Subscriber mission_type_subscriber = nh.subscribe("mission_type", 1, mission_type_callback);

	ros::ServiceClient set_mode_client = nh.serviceClient<mavros_msgs::SetMode>("/mavros/set_mode");

	krti18::State state;
	mavros_msgs::SetMode flight_mode;
	flight_mode.request.base_mode = 0;

	while(ros::ok()){
		ros::spinOnce();
		/*
		-1 ==> BREAK THE LOOP (EFFECT OF fm_changer.cpp ONLY)
		 1 ==> DROP (GUIDED -> MISSION -> AUTO)
		 2 ==> GO DOWN FOR MP (GUIDED -> MISSION -> LOITER)
		 3 ==> PICK UP MP (GUIDED -> MISSION -> AUTO)
		 else ==> DO NOTHING
	 	**go down for mp and pivk up mp mission sequence is separated
		  becuase it uses different cv detection method**
		*/
		if (mission_type == -1) break;
		
		else if (mission_type == 1) {
			state.doing_mission = true;
			copter_state_publisher.publish(state);

			flight_mode.request.custom_mode = "GUIDED";
			if (set_mode_client.call(flight_mode)) ROS_INFO("Flight mode changed to GUIDED");
			else ROS_INFO("WARNING : Failed to change flight mode to GUIDED");

			palapa707.go_center();
			palapa707.change_height(height_drop);
			palapa707.drop();
			palapa707.change_height(height_up);

			flight_mode.request.custom_mode = "AUTO";
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
			
			palapa707.go_center();
			palapa707.change_height(height_down);

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

			palapa707.change_height(height_mp);
			palapa707.go_center(); // Centering to get the MP
			palapa707.change_height(height_up);

			flight_mode.request.custom_mode = "AUTO";
			if (set_mode_client.call(flight_mode)) ROS_INFO("Flight mode changed to AUTO");
			else ROS_INFO("WARNING : Failed to change flight mode to AUTO");

			state.doing_mission = false;
			copter_state_publisher.publish(state);

			// Sleep to wait main.cpp change the value of mission_type
			usleep(200);
		}

	} // end of while(ros::ok())
	
	ROS_INFO("Mission Control is shutting down!");
	
	return 0;
}

void mission_type_callback (const krti18::Mission& data) {
	mission_type = data.mission_type;
}

/*
1. USLEEP SEBELUM count_validate DI-RESET : BUTUH BERAPA DETIK?
2. HATI-HATI BAROMETER BALA, KARENA KITA ADA MODE AUTO YANG BERGANTUNG PADA BAROMETER (BUKAN LIDAR)
3. KALIBRASI HSV MOMOGI ==> BIKIN KERANGKA
4. KALIBRASI NILAI validation_thresh
5. KALO MOOMOGI GAK KEDETECT, GEJALANYA SI COPTER LOITER KELAMAAN, RETRY!
   KALO YANG LAIN GAK KEDETECT, INSHAALLAH AMAN KARENA KEJEBAK DI MODE AUTO.
[X] 6. CEK APAKAH fm_changer BISA BALIK KE MODE STABILIZE? KALO SUDAH STABILIZE LAGI,
	   APAKAH PERGANTIAN MODE TETAP NORMAL TANPA HARUS MEMATIKAN ROS ATAU PERLU MATIKAN ROS? ==> COBA SEKARANG
7. UNTUK MISSION DROP, PIKIRIN MEKANISME TRIGGER EPM. (EPM SELALU NYALA, PADA SAAT MISI DROP
   UBAH OFF -> DELAY BENTAR -> ON IN LAGI)
8. CEK ORIENTASI KAMERA DAN VX_VY RELATIF PIXHAWK. PLOTTING!
9. CEK RUMUS PID. CEK NILAI ERROR.
10.BUAT ARDUINO.
11.CARA INCLUDE MAVROS APM.LAUNCH DI LAUNCH FILE KITA?
12.BUAT NODE UNTUK MASING-MASING GERAKAN
*/
