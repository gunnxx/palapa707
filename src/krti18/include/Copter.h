#ifndef COPTER
#define COPTER

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "krti18/Ardu.h"
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
    void go_down(float desired_alt);

  	/* ==========
  		  Callback
  	   ========== */
  	void cv_target_callback(const krti18::Shape& obj_loc);
  	void arduino_data_callback(const krti18::Ardu& data);
  	void timer_callback(const ros::TimerEvent& event);

  private:
  	ros::NodeHandle _nh;
  	ros::Publisher  _cmd_vel_publisher;
  	ros::Subscriber _cv_target_subscriber;
  	ros::Subscriber _arduino_data_subscriber;
  	ros::Timer 		_mission_timer;

  	/* ====================================
    		Detected Object (Square or Circle)
    		to be subscribed from _cv_det_sub
    		as /State for PID
  	   ==================================== */
  	int _x_det = 0;
  	int _y_det = 0;
  	int _r_det = 0;
  	float _safe_zone = 0.5;

  	/* ================================
    		Camera center location (pixel)
    		as /Setpoint for PID
  	   ================================ */
  	int _X_CAM = 320;
  	int _Y_CAM = 240;

  	/* ==========
  		  PID Gain
  	   ========== */
  	float _Kpx    = 0.002;
  	float _Kdx    = 0.000;
  	float _Kix    = 0.000;
  	float _max_ix = 0.050;
  	
  	float _Kpy    = 0.002;
  	float _Kdy    = 0.000;
  	float _Kiy    = 0.000;
  	float _max_iy = 0.050;

    float _Kpz    = 0.002;
    float _Kdz    = 0.000;
    float _Kiz    = 0.000;
    float _max_iz = 0.050;
    
  	/* ===============
  		  Mission Timer
  	   =============== */
  	float _mission_time = 5.; // seconds
  	bool _mission_timeout = false;

  	/* ==============
  		  Arduino Data
  	   ============== */
  	float _copter_alt = 0.;
  	bool _switch_status = false;
};

} // namespace UAV
#endif
