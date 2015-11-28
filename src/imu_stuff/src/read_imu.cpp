#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include "span_pose.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <visualization_msgs/Marker.h>
#include <cmath>
#include "latLong-UTMConversion.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Float32.h"

class Location
{
// Member Variables
private:
  ros::NodeHandle n;
  
  
// Member Functions
public:
  
  ros::Subscriber sub;
  ros::Publisher pub;
  ros::Publisher pub_lat;
  ros::Publisher pub_lon;
  ros::Publisher pub_yaw;  

  double lat;
  double lon;
  double yaw;
  double pix_x;
  double pix_y;
  
  std_msgs::Float64 boat_lat;
  std_msgs::Float64 boat_lon;
  std_msgs::Float32 boat_yaw;

  double ori_x;
  double ori_y;
  double grid_size;

  Location()
  {
    ori_x = -80.019460;
    ori_y = 40.477703;
    grid_size = 0.000042;
    sub = n.subscribe("recboat/span_pose", 10, &Location::Callback, this);
    pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
    pub_lat = n.advertise<std_msgs::Float64>("boat_lat", 10);
    pub_lon = n.advertise<std_msgs::Float64>("boat_lon", 10);
    pub_yaw = n.advertise<std_msgs::Float32>("boat_yaw", 10);

  }  
  
  //ros::Publisher pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 10);
  
  void Callback(const span_pose::span_pose &msg)
    {
    double north, east;
    UTM_ZONE_TYPE zone;

    lat = msg.lat;
    lon = msg.lon;
    yaw = msg.yaw;

    boat_lat.data = msg.lat;
    boat_lon.data = msg.lon;
    boat_yaw.data = msg.yaw;

    pub_lat.publish(boat_lat);
    pub_lon.publish(boat_lon);
    pub_yaw.publish(boat_yaw);


    pix_y =  1200 + (lat - ori_y)/grid_size;

    pix_x =   (lon - ori_x)/grid_size;

    std::cout << "lat: "  << lat
              << " lon: "  << lon
	      << " yaw: "  << yaw
              << " pix_x: "<< pix_x
              << " pix_y: "<< pix_y << '\n' ;
    //4.6638meter/pixel
    /*
    LLtoUTM(23, lat, lon, north, east, zone);

    std::cout << "lat: "  << lat
              << " lon: " << lon
              << "north: "<< north 
              << " east: " << east << '\n' ;
    */

   
    visualization_msgs::Marker points, line_list;
    points.header.frame_id  = line_list.header.frame_id = "/my_frame";
    points.header.stamp  = line_list.header.stamp = ros::Time::now();
    points.ns  = line_list.ns = "points_and_lines";
    points.action = line_list.action = visualization_msgs::Marker::ADD;
    points.pose.orientation.w  = line_list.pose.orientation.w = 0.0;



    points.id = 0;
    //line_strip.id = 1;
    line_list.id = 2;



    points.type = visualization_msgs::Marker::POINTS;
    //line_strip.type = visualization_msgs::Marker::LINE_STRIP;
    line_list.type = visualization_msgs::Marker::LINE_LIST;



    // POINTS markers use x and y scale for width/height respectively
    points.scale.x = 8;
    points.scale.y = 8;

    // LINE_STRIP/LINE_LIST markers use only the x component of scale, for the line width
    //line_strip.scale.x = 0.1;
    line_list.scale.x = 3;



    // Points are green
    points.color.g = 1.0f;
    points.color.a = 1.0;

    // Line strip is blue
    //line_strip.color.b = 1.0;
    //line_strip.color.a = 1.0;

    // Line list is red
    line_list.color.r = 1.0;
    line_list.color.a = 1.0;



    // Create the vertices for the points and lines
      
      
      
      geometry_msgs::Point p;
      p.x = pix_x;
      // - 40.407)*1000;
      p.y = pix_y;
      // + 79.953)*1000;
      p.z = 0;

      points.points.push_back(p);
      //line_strip.points.push_back(p);

      // The line list needs two points for each line
      line_list.points.push_back(p);
      p.z += 1.0;
      line_list.points.push_back(p);
    


    pub.publish(points);
    //marker_pub.publish(line_strip);
    pub.publish(line_list);

    

    

    //ROS_INFO_STREAM(lat<<","<<lon); 

  }
};

int main(int argc, char** argv)
{
  
  ros::init(argc, argv, "read_imu");
  Location lc;
  ros::spin();
  return 0;
}
