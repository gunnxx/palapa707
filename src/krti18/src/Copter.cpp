#include "Copter.h"

using namespace UAV;

/* ===============================
	CONSTRUCTOR AND DECONSTRUCTOR
   =============================== */

Copter::Copter(){
	//ROS_INFO("COPTER IS CREATED!");
	_cmd_vel_publisher        = _nh.advertise<geometry_msgs::Twist>("/mavros/setpoint_velocity/cmd_vel_unstamped", 10);
	_cv_target_subscriber     = _nh.subscribe("cv_target", 10, &Copter::cv_target_callback, this);
	_lidar_alt_subscriber	  = _nh.subscribe("lidar_alt", 10, &Copter::lidar_alt_callback, this);
	_switch_status_subscriber = _nh.subscribe("switch_status", 10, &Copter::switch_status_callback, this);
	_mission_timer 			  = _nh.createTimer(ros::Duration(_mission_time), &Copter::timer_callback, this);
}

Copter::~Copter(){
	//ROS_INFO("COPTER IS ERASED!");
}

/* ==========
	CALLBACK
   ========== */
void Copter::cv_target_callback(const krti18::Shape& obj_loc){
	_x_det = obj_loc.x_obj;
	_y_det = obj_loc.y_obj;
	_r_det = obj_loc.r_obj;
}

void Copter::lidar_alt_callback(const std_msgs::Int16& data){
	_copter_alt = data.data;
}

void Copter::switch_status_callback(const std_msgs::Bool& status){
	_switch_status = status.data;
}

void Copter::timer_callback(const ros::TimerEvent& event){
	bool _mission_timeout = true;
}

/* =================
	MOVEMENT METHOD
   ================= */

void Copter::go_center(){
	_mission_timer.start();

	// Keep track of old-error to measure Derivative
	float old_x_err = std::min(_X_CAM - _safe_zone*_r_det - _x_det,
							   _X_CAM + _safe_zone*_r_det - _x_det);
	float old_y_err = std::min(_Y_CAM - _safe_zone*_r_det - _y_det,
							   _Y_CAM + _safe_zone*_r_det - _y_det);

	// Set Integral starting value
	float ix_err = 0.;
	float iy_err = 0.;

	while (ros::ok() &&
		   !_mission_timeout && // Mission takes long time
		   !_switch_status) {   // Limit switch trigerred
		// Proportional error
		float x_err = std::min(_X_CAM - _safe_zone*_r_det - _x_det,
							   _X_CAM + _safe_zone*_r_det - _x_det);
		float y_err = std::min(_Y_CAM - _safe_zone*_r_det - _y_det,
							   _Y_CAM + _safe_zone*_r_det - _y_det);

		// Derivative error
		float dx_err = x_err - old_x_err;
		float dy_err = y_err - old_y_err;

		// Integral error
		ix_err = std::min(ix_err + x_err, _max_ix);
		iy_err = std::min(iy_err + y_err, _max_iy);

		// Output value
		float u_x = x_err*_Kpx + dx_err*_Kdx + ix_err*_Kix;
		float u_y = y_err*_Kpy + dy_err*_Kdy + iy_err*_Kiy;

		// Update old value
		old_x_err = x_err;
		old_y_err = y_err;

		// Publish output value (velocity that moves the copter)
		geometry_msgs::Twist vel;
		vel.linear.x = u_x;
		vel.linear.y = u_y;
		_cmd_vel_publisher.publish(vel);
	}

	// Reset timer
	_mission_timer.stop();
	_mission_timeout = false;
}

void Copter::drop(){
	/*

	ACTUATOR DOES SOMETHING HERE

	*/
}

void Copter::change_height(float desired_alt){
	_mission_timer.start();

	// Keep track of old-error to measure Derivative
	float old_z_err = desired_alt - _copter_alt;

	// Set Integral starting value
	float iz_err = 0.;

	while (ros::ok() &&
		   !_mission_timeout && // Mission takes long time
		   !_switch_status) {   // Limit switch trigerred
		// Proportional error
		float z_err = desired_alt - _copter_alt;

		// Derivative error
		float dz_err = z_err - old_z_err;

		// Integral error
		iz_err = std::min(iz_err + z_err, _max_iz);

		// Output value
		float u_z = z_err*_Kpz + dz_err*_Kdz + iz_err*_Kiz;

		// Update old value
		old_z_err = z_err;

		// Publish output value (velocity that moves the copter)
		geometry_msgs::Twist vel;
		vel.linear.z = u_z;
		_cmd_vel_publisher.publish(vel);
	}

	// Reset timer
	_mission_timer.stop();
	_mission_timeout = false;
}