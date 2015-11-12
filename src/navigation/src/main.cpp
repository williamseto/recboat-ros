/**********
 * main.cpp - Recboat basic navigation
 * Jeff McMahill (jmcm@nrec.ri.cmu.edu)
 * National Robotics Engineering Center, Carnegie Mellon University
 * Copyright (c) 2015 Carnegie Mellon University
 * All rights reserved.
 **********/

#include <math.h>

#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

#include <queue>

#include "vcu_relay/vcu_status.h"
#include "vcu_relay/vcu_cmd_drive.h"
#include "span_pose/span_pose.h"
#include "navigation/nav_cmd.h"
#include "navigation/nav_wpt.h"
#include "navigation/nav_yaw.h"
#include "navigation/nav_status.h"

#include "drive.h"

#define DRIVE_CMD_STOP   1
#define DRIVE_CMD_PAUSE  2
#define DRIVE_CMD_START  3
#define DRIVE_CMD_NEXT   4

#define DRIVE_STATE_IDLE    0
#define DRIVE_STATE_ACTIVE  1

#define DRIVE_MODE_WPT     0
#define DRIVE_MODE_YAW     1

struct wpt_type {
  double x;
  double y;
  float vel;
};

struct yaw_type {
  float yaw;
  float vel;
};

static int drive_cmd = 0;
static int drive_state = 0;
static wpt_type wpt_cur;
static int wpt_valid = 0;
static double start_x = 0.0;
static double start_y = 0.0;
static double la_x = 0.0;
static double la_y = 0.0;
static int reset_start = 0;

static yaw_type yaw_cur;

static int drive_mode = DRIVE_MODE_WPT;

static ros::Publisher drive_pub;

#define WPT_IMMEDIATE     1  /* override current goal */
#define WPT_ADD           2  /* set goal or add to list */
#define WPT_CLEAR         3  /* clear list */

std::queue<struct wpt_type> wpt_que;

/* clear waypoint list */
static void wpt_clear()
{

  wpt_valid = 0;
  
  while (!wpt_que.empty())
    wpt_que.pop();
}

/* advance to the next waypoint, return 0 if there are no more */
static int wpt_next()
{

  if (wpt_que.empty()) return(0);

  wpt_cur = wpt_que.front();
  wpt_valid = 1;
  printf("next waypoint ok\n");

  wpt_que.pop();

  return(1);
}

/* return 1 if we are at the end of the list */
static int wpt_end()
{

  return(wpt_que.empty());
}

/* add a waypoint to the list */
static int wpt_add(double x, double y, float vel)
{
  struct wpt_type wpt;

  wpt.x = x;
  wpt.y = y;
  wpt.vel = vel;

  wpt_que.push(wpt);
  
  return(0);
}

void nav_cmd_cb(const navigation::nav_cmd::ConstPtr& msg)
{

  drive_cmd = msg->cmd;

  printf("nav cmd: %d wpt_valid: %d\n", drive_cmd, wpt_valid);

  /* clear waypoint on stop command */
  if (msg->cmd == DRIVE_CMD_STOP) wpt_clear();

  if (msg->cmd == DRIVE_CMD_NEXT) {
    if (wpt_next()) {
      reset_start = 1;
      drive_cmd = DRIVE_CMD_START;
    } else {
      drive_cmd = DRIVE_CMD_STOP;
    }
  }

  /* ignore start if we don't have a waypoint */
  if ((drive_cmd == DRIVE_CMD_START) && !wpt_valid)
    drive_cmd = DRIVE_CMD_STOP;

}

void nav_wpt_cb(const navigation::nav_wpt::ConstPtr& msg)
{

  //  drive_mode = DRIVE_MODE_WPT;

  /* override any current goal point */
  if (msg->action == WPT_IMMEDIATE) {
    wpt_cur.x = msg->east;
    wpt_cur.y = msg->north;
    wpt_cur.vel = msg->vel;
    wpt_valid = 1;
    reset_start = 1;
  } else if (msg->action == WPT_ADD) {  /* add to the end of the list */
    printf("wpt: %f %f [%d]\n", msg->east, msg->north, wpt_valid);
    /* if we're not already navigating, set this as the current goal */
    if (!wpt_valid) {
      wpt_valid = 1;
      wpt_cur.x = msg->east;
      wpt_cur.y = msg->north;
      wpt_cur.vel = msg->vel;
    } else {  /* otherwise add it to the list */
      wpt_add(msg->east, msg->north, msg->vel);
    }
  } else if (msg->action == WPT_CLEAR) {  /* clear all waypoints */
    wpt_clear();
  }

}

void nav_yaw_cb(const navigation::nav_yaw::ConstPtr& msg)
{

  drive_mode = DRIVE_MODE_YAW;

  yaw_cur.vel = msg->vel;
  yaw_cur.yaw = msg->yaw;

  printf("yaw: %f\n", yaw_cur.yaw);

}

void pose_cb(const span_pose::span_pose::ConstPtr& msg)
{
  int ret;
  float throttle = 0.0, steer = 0.0;
  int flags = 0;
  vcu_relay::vcu_cmd_drive drive_msg;

  if ((drive_mode == DRIVE_MODE_WPT) && !wpt_valid) drive_cmd = DRIVE_CMD_STOP;

  if ((drive_cmd == DRIVE_CMD_START) &&
      (drive_state != DRIVE_STATE_ACTIVE) &&
      ((drive_mode == DRIVE_MODE_YAW) || wpt_valid)) {
    drive_state = DRIVE_STATE_ACTIVE;
    reset_start = 1;
  }
  if (drive_cmd == DRIVE_CMD_STOP) {
    drive_state = DRIVE_STATE_IDLE;
  }
  if (drive_cmd == DRIVE_CMD_PAUSE) {
    drive_state = DRIVE_STATE_IDLE;
  }

  if (reset_start) {
    printf("reset start\n");
    reset_start = 0;
    flags |= DRIVE_RESET;
    start_x = msg->east;  /* set start to current position */
    start_y = msg->north;
  }

  if (drive_state == DRIVE_STATE_ACTIVE) {
    if (drive_mode == DRIVE_MODE_WPT) {
      if (wpt_end())
        flags |= DRIVE_END;
      ret = drive_pure_pursuit_seg(flags, wpt_cur.vel,
                                   start_x, start_y, wpt_cur.x, wpt_cur.y,
                                   msg->east, msg->north, M_PI/2.0-msg->yaw,
                                   &la_x, &la_y, &throttle, &steer);
      if (!ret) {  /* end of segment */
        start_x = wpt_cur.x;  /* set start point to previous waypoint */
        start_y = wpt_cur.y;
        if (!wpt_next()) {
          printf("end of waypoints!\n");
          drive_state = DRIVE_STATE_IDLE;
          wpt_valid = 0;
          throttle = 0.0;
          steer = 0.0;
        }
      }
    } else if (drive_mode == DRIVE_MODE_YAW) {
      ret = drive_servo_yaw(flags, yaw_cur.vel, yaw_cur.yaw,
                            msg->east, msg->north, M_PI/2.0-msg->yaw,
                            &throttle, &steer);
    } else {
      throttle = 0.0;
      steer = 0.0;
    }
  }

  /* TODO: check vcu state */

  drive_msg.port = throttle;
  drive_msg.stbd = throttle;
  drive_msg.steer = steer;

  drive_pub.publish(drive_msg);

}

void vcu_cb(const vcu_relay::vcu_status::ConstPtr& msg)
{


}

int main(int argc, char **argv)
{
  navigation::nav_status status_msg;

  ros::init(argc, argv, "navigation");

  ros::NodeHandle n;

  ros::Publisher status_pub = n.advertise<navigation::nav_status>("recboat/nav_status", 10);
  drive_pub = n.advertise<vcu_relay::vcu_cmd_drive>("recboat/vcu_cmd_drive", 10);

  ros::Subscriber nav_cmd_sub = n.subscribe("recboat/nav_cmd", 10, nav_cmd_cb);
  ros::Subscriber nav_wpt_sub = n.subscribe("recboat/nav_wpt", 100, nav_wpt_cb);
  ros::Subscriber nav_yaw_sub = n.subscribe("recboat/nav_yaw", 100, nav_yaw_cb);

  ros::Subscriber pose_sub = n.subscribe("recboat/span_pose", 10, pose_cb);

  ros::Subscriber vcu_sub = n.subscribe("recboat/vcu_status", 10, vcu_cb);

  ros::Rate loop_rate(10);

  while (ros::ok())
  {

    status_msg.start_north = start_y;
    status_msg.start_east = start_x;
    status_msg.goal_north = wpt_cur.y;
    status_msg.goal_east = wpt_cur.x;
    status_msg.la_north = la_y;
    status_msg.la_east = la_x;
    status_msg.state = drive_state;
    status_msg.header.stamp = ros::Time::now();
    status_pub.publish(status_msg);

    ros::spinOnce();

    loop_rate.sleep();

  }

  return 0;
}
