#include "boatlocation.h"
#include <tf/transform_datatypes.h>

 BoatLocation :: BoatLocation(ros::NodeHandle *nodeHandle, double refx, double refy, double scalex, double scaley,int height)
 {
        boatGoal.m_newgoal = false;
        boatPosition.m_boatX = 0;
        boatPosition.m_boatY = 0;
        boatPosition.m_boatYaw = 0;
        SetMapReference (refx, refy, scalex, scaley, height);
        m_poseSub = nodeHandle->subscribe("recboat/span_pose", 1, &BoatLocation::poseCB, this);
        m_goalSub = nodeHandle->subscribe("move_base_simple/goal", 1, &BoatLocation::goalCB, this);
 }
    
 void BoatLocation :: SetMapReference(double refx, double refy, double scalex, double scaley,int height)
 {
        mapreference.map_ref_x = refx;
        mapreference.map_ref_y = refy;
        mapreference.map_scale_x = scalex;
        mapreference.map_scale_y = scaley;
        mapreference.map_pix_height = height;
 }
 
 void BoatLocation :: poseCB(const span_pose::span_pose &msg)
 {
        boatPosition.m_boatX = (msg.east - mapreference.map_ref_x)/mapreference.map_scale_x;
        boatPosition.m_boatY = mapreference.map_pix_height + (msg.north - mapreference.map_ref_y)/mapreference.map_scale_y;
        boatPosition.m_boatYaw = msg.yaw;
       // std::cout<<"\nUpdating Pose\n"<<"X: "<<boatPosition.m_boatX<<" Y: "<<boatPosition.m_boatY<<" Z: "<<boatPosition.m_boatYaw;
 }
 
 void BoatLocation :: goalCB(const geometry_msgs::PoseStamped &msg)
 {
       //get yaw from 2d nav goal for path planner
        tf::Quaternion q(msg.pose.orientation.x,
                         msg.pose.orientation.y,
                         msg.pose.orientation.z,
                         msg.pose.orientation.w);
        tf::Matrix3x3 m(q);
        double roll, pitch, yaw;
        m.getRPY(roll, pitch, yaw);        

        boatGoal.m_goalX = msg.pose.position.x;
        boatGoal.m_goalY = msg.pose.position.y;
        boatGoal.m_goalTheta = yaw;
        boatGoal.m_newgoal = true;
  } 
  
 BoatPosition BoatLocation :: getPosition()
 {
        return boatPosition;
 }
 
 BoatGoal BoatLocation :: getGoal()
 {
     return boatGoal;
 }
 
 void BoatLocation :: setGoalFalse ()
 {
     boatGoal.m_newgoal = false;
 }
 