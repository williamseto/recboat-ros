#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>

int NUM = 5;
int imno = 0;

/**
Class to flip the image.
**/
class Filter
{
// Member Variables
private:
	ros::NodeHandle nh_;
	image_transport::ImageTransport it_;
	image_transport::Subscriber image_sub_;
	image_transport::Publisher image_pub_;
  
// Member Functions
public:
	Filter(): it_(nh_)
  	{
	// Subscrive to input video feed and publish output video feed
	image_sub_ = it_.subscribe("/radar_raw_will", 1, &Filter::imageCb, this);
	image_pub_ = it_.advertise("/pirate_filter/image", 1);
	}

  	// Destructor for nothing
  	~Filter()
  	{

  	}

	void imageCb(const sensor_msgs::ImageConstPtr& msg)
  	{
    		cv_bridge::CvImagePtr cv_ptr;
    		try
    		{
      			cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    		}
    		
		catch (cv_bridge::Exception& e)
    		{
      			ROS_ERROR("cv_bridge exception: %s", e.what());
      			return;
    		}

	char buffer[33];
        snprintf(buffer, sizeof(buffer), "%d", imno++);
        std::string name = std::string("image_") + buffer + std::string(".png");
	cv::imwrite(name, cv_ptr->image);			
    	// Flip the image
    	//cv::flip(cv_ptr->image, cv_ptr->image, -1);
	cv::Mat gray, thresh;
	cv::cvtColor(cv_ptr->image, gray, CV_BGR2GRAY);
	cv::threshold(gray, thresh, 65, 255, cv::THRESH_BINARY);
	int morph_size = NUM;
	std::cout << morph_size << std::endl;
    	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size( 2*morph_size + 1, 2*morph_size+1 ), cv::Point( morph_size, morph_size ) );
	cv::morphologyEx(thresh, thresh, cv::MORPH_DILATE, element);
	//cv::namedWindow("Image", cv::WINDOW_NORMAL);cv::imshow("Image", thresh);cv::waitKey();
	std::vector<std::vector<cv::Point> > contours;
  	std::vector<cv::Vec4i> hierarchy;   	
	findContours(thresh, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );
	int count  = 1;
	for( int i = 0; i< contours.size(); i++ )
		if(cv::contourArea(contours[i]) > 100)
     	{
       		cv::Scalar color = cv::Scalar(255, 0, 0);
       		cv::drawContours( cv_ptr->image, contours, i, color, 2, 10, hierarchy, 0, cv::Point() );
		char buffer[33];
		snprintf(buffer, sizeof(buffer), "%d", count++);
		std::string name = std::string("Ob No. ") + buffer;	
		// cv::putText(cv_ptr->image, name, contours[i][1], CV_FONT_HERSHEY_COMPLEX, 1, color, 3, 2);
     	}
		image_pub_.publish(cv_bridge::CvImage(std_msgs::Header(), "bgr8", cv_ptr->image).toImageMsg());
	for( int i = 0; i< contours.size(); i++ ){std::cout << "New Object Detected --> ";
		for( int j = 0; j < contours[i].size(); j++ ){
			std::cout << contours[i][j] << "\t";
	}std::cout<<std::endl;}

	
	//cv::namedWindow("Image", cv::WINDOW_NORMAL);cv::imshow("Image", thresh);cv::waitKey();
	
  	}
};

void help(){
	std::cout << "Usage ./detect_obs <size-of-morphology>" << std::endl;
	exit(1);
}

int main(int argc, char** argv)
{
  if(argc!=2)
	help();
  NUM = atoi(argv[1]);
  ros::init(argc, argv, "detect_obs");
  Filter fp;
  ros::spin();
  return 0;
}
