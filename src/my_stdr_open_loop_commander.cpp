#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
//node to send Twist commands to the Simple 2-Dimensional Robot Simulator via cmd_vel
int main(int argc, char **argv) {
    ros::init(argc, argv, "my_stdr_commander"); 
    ros::NodeHandle n; // two lines to create a publisher object that can talk to ROS
    ros::Publisher twist_commander = n.advertise<geometry_msgs::Twist>("/robot0/cmd_vel", 1);
    //some "magic numbers"
    double sample_dt = 0.01; //specify a sample period of 10ms  
    double speed = 1.0; // 1m/s speed command
    double yaw_rate = 0.5; //0.5 rad/sec yaw rate command
    double large_negative_yaw_rate = -0.7; //-0.7 rad/sec yaw rate command
    double negative_yaw_rate = -0.5; // -0.5 rad/sec yaw rate command
    double time_5_sec = 5.0; // should move 5 meters or 2.5 rad in 5 seconds
    double time_3_sec = 3.0; // should move 3 meters or 1.5 rad in 3 seconds
    double time_2_sec = 2.0; // should move 2 meters or 1 rad in 2 seconds
    double time_175_sec = 1.75; // should move 1.5 meters or .75 rad in 1.5 second
    double time_1_sec = 1.0; // should move 1 meters or .5 rad in 1 second
    double time_h_sec = 0.5; // should move .5 meters or .25 rad in 1 second
    
      
    geometry_msgs::Twist twist_cmd; //this is the message type required to send twist commands to STDR 
    // start with all zeros in the command message; should be the case by default, but just to be safe..
    twist_cmd.linear.x=0.0;
    twist_cmd.linear.y=0.0;    
    twist_cmd.linear.z=0.0;
    twist_cmd.angular.x=0.0;
    twist_cmd.angular.y=0.0;
    twist_cmd.angular.z=0.0;   

    ros::Rate loop_timer(1/sample_dt); //create a ros object from the ros “Rate” class; set 100Hz rate     
    double timer=0.0;
    //start sending some zero-velocity commands, just to warm up communications with STDR
    for (int i=0;i<10;i++) {
      twist_commander.publish(twist_cmd);
      loop_timer.sleep();
    }
    twist_cmd.linear.x=speed; //command to move forward
    while(timer<time_2_sec) {
          twist_commander.publish(twist_cmd);
          timer+=sample_dt;
          loop_timer.sleep();
          }
    twist_cmd.angular.z=yaw_rate; //and start spinning CCR and keep moving
    timer=0.0; //reset the timer
    while(timer<time_2_sec) {
          twist_commander.publish(twist_cmd);
          timer+=sample_dt;
          loop_timer.sleep();
          }

    twist_cmd.angular.z=negative_yaw_rate; //spinning CC but continuing to move forward
    timer=0.0; //reset the timer
    while(timer<time_2_sec) {
          twist_commander.publish(twist_cmd);
          timer+=sample_dt;
          loop_timer.sleep();
          }
    
    twist_cmd.angular.z=yaw_rate; //spinning CCR but continuing to move forward
    timer=0.0; //reset the timer
    while(timer<time_5_sec) {
          twist_commander.publish(twist_cmd);
          timer+=sample_dt;
          loop_timer.sleep();
          }

    twist_cmd.angular.z=0; //stop spinning but continue moving forward
    timer=0.0; //reset the timer
    while(timer<time_175_sec) {
          twist_commander.publish(twist_cmd);
          timer+=sample_dt;
          loop_timer.sleep();
          }

    twist_cmd.angular.z=yaw_rate; //spinning CCR but continuing to move forward
    timer=0.0; //reset the timer
    while(timer<time_1_sec) {
          twist_commander.publish(twist_cmd);
          timer+=sample_dt;
          loop_timer.sleep();
          }

    twist_cmd.angular.z=large_negative_yaw_rate; //spinning CC but continuing to move forward
    timer=0.0; //reset the timer
    while(timer<time_2_sec) {
          twist_commander.publish(twist_cmd);
          timer+=sample_dt;
          loop_timer.sleep();
          }

    twist_cmd.angular.z=0; //stop spinning but continue moving forward
    timer=0.0; //reset the timer
    while(timer<time_2_sec) {
          twist_commander.publish(twist_cmd);
          timer+=sample_dt;
          loop_timer.sleep();
          }

    twist_cmd.angular.z=yaw_rate; //spinning CCR but continuing to move forward
    timer=0.0; //reset the timer
    while(timer<time_3_sec) {
          twist_commander.publish(twist_cmd);
          timer+=sample_dt;
          loop_timer.sleep();
          }

    twist_cmd.angular.z=0; //stop spinning but continue moving forward
    timer=0.0; //reset the timer
    while(timer<time_3_sec) {
          twist_commander.publish(twist_cmd);
          timer+=sample_dt;
          loop_timer.sleep();
          }

    //halt the motion
    twist_cmd.angular.z=0.0; 
    twist_cmd.linear.x=0.0; 
    for (int i=0;i<10;i++) {
      twist_commander.publish(twist_cmd);
      loop_timer.sleep();
    }               
    //done commanding the robot; node runs to completion
}

