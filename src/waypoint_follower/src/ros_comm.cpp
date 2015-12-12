/**********
Interface to communicate with ROS and the waypoint follower
 **********/
#include "ros/ros.h"

#include "std_msgs/String.h"
#include <iostream>
#include <fstream>

#include "vcu_relay/vcu_cmd_stop.h"
#include "navigation/nav_cmd.h"
#include "navigation/nav_wpt.h"
#include "navigation/nav_status.h"
#include "span_pose/span_pose.h"

#include "ros_comm.h"
using namespace std;



ros::Publisher nav_cmd_pub;
ros::Publisher nav_wpt_pub;
ros::Publisher vcu_stop_pub;

ros::Subscriber pose_sub;


void pose_cb(const span_pose::span_pose::ConstPtr& msg)
{

  cur_pose_status.lat = msg->lat;
  cur_pose_status.lon = msg->lon;

  cur_pose_status.north = msg->north;
  cur_pose_status.east = msg->east;
  cur_pose_status.alt = msg->z;

  cur_pose_status.roll = msg->roll;
  cur_pose_status.pitch = msg->pitch;
  cur_pose_status.yaw = msg->yaw;

  cur_pose_status.vel = msg->vel;

  cur_pose_status.nsat = msg->nsat;
  cur_pose_status.ins_stat = msg->ins_stat;
  cur_pose_status.sol = msg->sol;
  cur_pose_status.pos = msg->pos;
  strncpy(cur_pose_status.ins_str, msg->ins_str.c_str(), sizeof(cur_pose_status.ins_str));
  cur_pose_status.ins_str[sizeof(cur_pose_status.ins_str)-1] = 0;

  strncpy(cur_pose_status.sol_str, msg->sol_str.c_str(), sizeof(cur_pose_status.sol_str));
  cur_pose_status.sol_str[sizeof(cur_pose_status.sol_str)-1] = 0;

  strncpy(cur_pose_status.pos_str, msg->pos_str.c_str(), sizeof(cur_pose_status.pos_str));
  cur_pose_status.pos_str[sizeof(cur_pose_status.pos_str)-1] = 0;

}


int ros_nav_cmd(int cmd)
{
  navigation::nav_cmd msg;

  msg.cmd = cmd;
  nav_cmd_pub.publish(msg);

  return(0);
}

int ros_nav_wpt(double north, double east, float vel, int action)
{

  navigation::nav_wpt msg;

  msg.north = north;
  msg.east = east;
  msg.vel = vel;
  msg.action = action;

  nav_wpt_pub.publish(msg);
  cout<<"\nnorth: "<<msg.north<<" East: "<< msg.east << " Vel: " <<msg.vel<<" action: "<<msg.action;

  return(0);
}

int ros_vcu_estop(int state)
{
  vcu_relay::vcu_cmd_stop msg;

  msg.stop = state;
  vcu_stop_pub.publish(msg);

  return(0);
}


int ros_init(int *argc, char ***argv)
{

 ros::init(*argc, *argv, "recboat_wpt");

  return 0;
}

void *ros_thread(void *d)
{
  ros::NodeHandle n;

  nav_cmd_pub = n.advertise<navigation::nav_cmd>("recboat/nav_cmd", 10);
  nav_wpt_pub = n.advertise<navigation::nav_wpt>("recboat/nav_wpt", 100);

  pose_sub = n.subscribe("recboat/span_pose", 10, pose_cb);
  ros::spin();
}

void ros_exit()
{

  ros::shutdown();

}
