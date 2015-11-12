#ifndef FILTER_H
#define FILTER_H

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class Filter{
private:
	ros::NodeHandle nh_;
	image_transport::ImageTransport it_;
	image_transport::Subscriber image_sub_;
	image_transport::Publisher image_pub_;
 
public:
	Filter();
	~Filter();
	void imageCb(const sensor_msgs::ImageConstPtr& msg);
};

#endif // FILTER_H
