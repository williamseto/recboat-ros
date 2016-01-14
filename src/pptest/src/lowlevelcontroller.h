#ifndef LOWLEVELCONTROLLER_H
#define LOWLEVELCONTROLLER_H

#include <ros/ros.h>

class LowlevelController
{
    ros::Publisher  m_nav_cmd_pub;
    ros::Publisher  m_nav_wpt_pub;
public: 
    LowlevelController(ros::NodeHandle *);
    int ros_nav_cmd(int);
    int ros_nav_wpt(double, double, float, int);
};

#endif