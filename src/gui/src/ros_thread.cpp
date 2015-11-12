/**********
 * ros_thread.cpp - Recboat gui ROS interface
 * Jeff McMahill (jmcm@nrec.ri.cmu.edu)
 * National Robotics Engineering Center, Carnegie Mellon University
 * Copyright (c) 2015 Carnegie Mellon University
 * All rights reserved.
 **********/

#include "ros/ros.h"

#include "std_msgs/String.h"
#include <iostream>
#include <fstream>

#include "vcu_relay/vcu_status.h"
#include "vcu_relay/vcu_cmd_stop.h"
#include "span_pose/span_pose.h"
#include "navigation/nav_cmd.h"
#include "navigation/nav_wpt.h"
#include "navigation/nav_status.h"

#include "ros_wrapper.h"

extern "C" {
  struct ros_vcu_status cur_vcu_status;
  struct ros_pose_status cur_pose_status;
  struct ros_nav_status cur_nav_status;

  /* callback to GUI */
  void pose_update(struct ros_pose_status *pose);
}

ros::Publisher nav_cmd_pub;
ros::Publisher nav_wpt_pub;
ros::Publisher vcu_stop_pub;

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

  pose_update(&cur_pose_status);

}

void nav_status_cb(const navigation::nav_status::ConstPtr& msg)
{

  cur_nav_status.start_north = msg->start_north;
  cur_nav_status.start_east = msg->start_east;

  cur_nav_status.goal_north = msg->goal_north;
  cur_nav_status.goal_east = msg->goal_east;

  cur_nav_status.la_north = msg->la_north;
  cur_nav_status.la_east = msg->la_east;

  cur_nav_status.state = msg->state;

}

void vcu_status_cb(const vcu_relay::vcu_status::ConstPtr& msg)
{

  cur_vcu_status.state = msg->state;

  cur_vcu_status.port_throttle = msg->port_throttle;
  cur_vcu_status.stbd_throttle = msg->stbd_throttle;
  cur_vcu_status.port_shift = msg->port_shift;
  cur_vcu_status.stbd_shift = msg->stbd_shift;

  cur_vcu_status.port_throttle_out = msg->port_throttle_out;
  cur_vcu_status.stbd_throttle_out = msg->stbd_throttle_out;

  cur_vcu_status.steer_angle = msg->steer_angle;

  cur_vcu_status.hci_switch = msg->hci_switch;
  cur_vcu_status.port_ind = msg->port_ind;
  cur_vcu_status.stbd_ind = msg->stbd_ind;

  cur_vcu_status.remote_select = msg->remote_select;
  cur_vcu_status.autoled = msg->autoled;

  cur_vcu_status.have_ctrl = msg->have_ctrl;

  cur_vcu_status.steer_angle_req = msg->steer_angle_req;
  cur_vcu_status.steer_mode = msg->steer_mode;

  cur_vcu_status.rt_amps = msg->rt_amps;
  cur_vcu_status.rt_bamps = msg->rt_bamps;
  cur_vcu_status.rt_ff = msg->rt_ff;
  cur_vcu_status.rt_fm = msg->rt_fm;
  cur_vcu_status.rt_fs = msg->rt_fs;
  cur_vcu_status.rt_power = msg->rt_power;
  cur_vcu_status.rt_temp = msg->rt_temp;
  cur_vcu_status.rt_volt = msg->rt_volt;

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

  return(0);
}

int ros_vcu_estop(int state)
{
  vcu_relay::vcu_cmd_stop msg;

  msg.stop = state;
  vcu_stop_pub.publish(msg);

  return(0);
}

void *ros_thread(void *d)
{


  /* publish:
     nav_cmd
     nav_wpt
     vcu_cmd_stop
  */
  ros::NodeHandle n;

  nav_cmd_pub = n.advertise<navigation::nav_cmd>("recboat/nav_cmd", 10);
  nav_wpt_pub = n.advertise<navigation::nav_wpt>("recboat/nav_wpt", 100);
  vcu_stop_pub = n.advertise<vcu_relay::vcu_cmd_stop>("recboat/vcu_cmd_stop", 10);

  /*
     subscribe:
     nav_status
     vcu_status
     span_pose
   */

  ros::Subscriber nav_status_sub = n.subscribe("recboat/nav_status", 10, nav_status_cb);
  ros::Subscriber vcu_status_sub = n.subscribe("recboat/vcu_status", 10, vcu_status_cb);
  ros::Subscriber pose_sub = n.subscribe("recboat/span_pose", 10, pose_cb);

  ros::spin();

}

void ros_init(int *argc, char ***argv)
{

  ros::init(*argc, *argv, "recboat_gui");

}

void ros_exit()
{

  ros::shutdown();

}
