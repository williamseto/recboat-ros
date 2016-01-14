#ifndef MAKERVIZ_H
#define MAKERVIZ_H
 
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <string.h>

enum MarkerType
{
  POINTS,
  LINE_STRIP,
  LINE_LIST  
};

class MarkerRVIZ
{
  private: 
  static ros::Publisher markerPub;
  visualization_msgs::Marker pointMarker;
  geometry_msgs::Point p;
  public:   
  MarkerRVIZ(ros::NodeHandle *, std::string, std::string, MarkerType, float, float, float);
  void UpdateGUI(double, double, double);
  void ClearMarker();
};

#endif