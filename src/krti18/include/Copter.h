#ifndef COPTER
#define COPTER

#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include "std_msgs/Int16.h"
#include "geometry_msgs/Twist.h"
#include "krti18/Shape.h"
#include "krti18/State.h"

namespace UAV{

class Copter {
  public:
  	Copter();
  	~Copter();

  	/* ========================
  		  Copter movement method
  	   ======================== */
  	void go_center();
    void drop();
    void get();
    void change_height(float desired_alt);

  	/* ==========
  		  Callback
  	   ========== */
  	void cv_target_callback(const krti18::Shape& obj_loc);
  	void lidar_alt_callback(const std_msgs::Int16& data);
    void switch_status_callback(const std_msgs::Bool& status);
  	void timer_callback(const ros::TimerEvent& event);

  private:
  	ros::NodeHandle _nh;
  	
    ros::Publisher  _cmd_vel_publisher;
    ros::Publisher  _left_servo_publisher;
    ros::Publisher  _right_servo_publisher;
  	
    ros::Subscriber _cv_target_subscriber;
  	ros::Subscriber _lidar_alt_subscriber;
    ros::Subscriber _switch_status_subscriber;
  	
    ros::Timer 		  _mission_timer;

  	/* ====================================
    		Detected Object (Square or Circle)
    		to be subscribed from _cv_det_sub
    		as /State for PID
  	   ==================================== */
  	int _x_det = 0;
  	int _y_det = 0;
  	int _r_det = 0;
  	const float _safe_zone = 0.5;

  	/* ================================
    		Camera center location (pixel)
    		as /Setpoint for PID
  	   ================================ */
  	const int _X_CAM = 320;
  	const int _Y_CAM = 240;

  	/* ==========
  		  PID Gain
  	   ========== */
  	const float _Kpx    = 0.002;
  	const float _Kdx    = 0.000;
  	const float _Kix    = 0.000;
  	const float _max_ix = 0.050;
  	
  	const float _Kpy    = 0.002;
  	const float _Kdy    = 0.000;
  	const float _Kiy    = 0.000;
  	const float _max_iy = 0.050;

    const float _Kpz    = 0.002;
    const float _Kdz    = 0.000;
    const float _Kiz    = 0.000;
    const float _max_iz = 0.050;
    
  	/* ===============
  		  Mission Timer
  	   =============== */
  	const float _mission_time = 5.; // seconds
  	bool _mission_timeout = false;

  	/* ==============
  		  Arduino Data
  	   ============== */
  	bool _switch_status     = false;
    int  _copter_alt        = 0.;
    int  _drop_servo_degree = 0;
    int  _get_servo_degree  = 120;
};

} // namespace UAV
#endif
