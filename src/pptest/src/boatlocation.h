#ifndef BOATLOCATION_H
#define BOATLOCATION_H
 

#include <ros/ros.h>
#include "span_pose/span_pose.h"
#include <geometry_msgs/PoseStamped.h>

struct MapReference
{
double map_ref_x;
double map_ref_y;
double map_scale_x;
double map_scale_y;
int map_pix_height;
};

struct BoatPosition
{
     double m_boatX;
     double m_boatY;
     double m_boatYaw;
};

struct BoatGoal
{
  double m_goalX;
  double m_goalY;
  double m_goalTheta;
  bool m_newgoal;
};

class BoatLocation
{
    private: 
    ros::Subscriber m_poseSub; 
    ros::Subscriber m_goalSub;
    BoatPosition boatPosition;
    BoatGoal boatGoal;
    
    public:   
    MapReference mapreference;  
    
    BoatLocation(ros::NodeHandle *, double , double , double , double, int);
    void SetMapReference(double , double , double, double ,int);
    void poseCB(const span_pose::span_pose &);
    void goalCB(const geometry_msgs::PoseStamped &);
    BoatPosition getPosition(); 
    BoatGoal getGoal();
    void setGoalFalse();
};

#endif