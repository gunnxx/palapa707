/*  Configuration
    //LIDAR WIRING
    KABEL KUNING  >>  PIN
    KABEL ORANYE  >>  PIN
    KABEL MERAH   >>  +5V
    KABEL HITAM   >>  GND
 */
#include <Servo.h>
#include <ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Int32.h>

unsigned long pulseWidth;
unsigned long distance_before;
unsigned long distance_now;
float alpha=0.75;

const int trigPin         = 2;
const int echoPin         = 3;
const int servoPin_Right  = 10;
const int servoPin_Left   = 9;

int servoData_Right=0;
int servoData_Left=0;

Servo myServo_Right;
Servo myServo_Left;

void servo_right_callback(const std_msgs::Int16& data){
    servoData_Right = data.data;
}

void servo_left_callback(const std_msgs::Int16& data){
    servoData_Left = data.data; 
}

//ROS
ros::NodeHandle nh;
std_msgs::Int16 sonar;
ros::Publisher pub_sonar("lidar_alt", &sonar);
ros::Subscriber<std_msgs::Int16> sub_right("right_servo", &servo_right_callback);
ros::Subscriber<std_msgs::Int16> sub_left("left_servo", &servo_left_callback);

void setup(){
  Serial.begin(57600);                    //Start serial communications
  myServo_Right.attach(servoPin_Right);
  myServo_Left.attach(servoPin_Left);
  
  nh.initNode();
  nh.advertise(pub_sonar);
  nh.subscribe(sub_right);
  nh.subscribe(sub_left);
  
  pinMode(trigPin, OUTPUT);       //Set pin 2 as trigger pin
  pinMode(echoPin, INPUT);        //Set pin 3 as monitor pin
  digitalWrite(trigPin, LOW);     //Set trigger LOW for continuous read
  delay(1000);
}

void loop(){
  pulseWidth = pulseIn(3, HIGH);    //Count how long the pulse is high in microseconds
   
  // If we get a reading that isn't zero, let's print it
  if(pulseWidth != 0){
    distance_now = (alpha*(pulseWidth/10)) + ((1-alpha)*distance_before);   //10usec = 1 cm of distance
    //Serial.print("Distance = ");    //Print the distance
    //Serial.println(distance_now);
    distance_before = distance_now;
    sonar.data = distance_now;
    pub_sonar.publish(&sonar);
  }
  
  myServo_Right.write(servoData_Right);
  myServo_Left.write(servoData_Left);
  
  nh.spinOnce();
  delay(1);
}
