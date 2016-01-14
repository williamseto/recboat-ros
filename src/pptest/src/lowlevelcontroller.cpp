#include "lowlevelcontroller.h"
#include "navigation/nav_cmd.h"
#include "navigation/nav_wpt.h"



LowlevelController :: LowlevelController(ros::NodeHandle *nodeHandle)
{
       m_nav_cmd_pub = nodeHandle->advertise<navigation::nav_cmd>("recboat/nav_cmd", 10);
       m_nav_wpt_pub = nodeHandle->advertise<navigation::nav_wpt>("recboat/nav_wpt", 100);
}

int LowlevelController :: ros_nav_cmd(int cmd)
{
      navigation::nav_cmd msg;

      msg.cmd = cmd;
      m_nav_cmd_pub.publish(msg);

      return(0);
}
    
int LowlevelController :: ros_nav_wpt(double north, double east, float vel, int action)
{
      navigation::nav_wpt msg;

      msg.north = north;
      msg.east = east;
      msg.vel = vel;
      msg.action = action;

      m_nav_wpt_pub.publish(msg);

      return(0);
}