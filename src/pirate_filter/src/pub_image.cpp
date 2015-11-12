#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <iostream>

void help(){
	std::cout << "ERROR:: Argument 1 missing. \n USAGE:: ./pub_image <image_path> \n";
	exit(1);
}

int main(int argc, char ** argv){
	if(argc!=2)
		help();	
	ros::init(argc, argv, "pub_image");
	ros::NodeHandle nh;
	image_transport::ImageTransport it(nh);
	image_transport::Publisher pub = it.advertise("pirate_raw/image", 1);
	cv::Mat im = cv::imread(argv[1]);
	sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", im).toImageMsg();
	ros::Rate loop_rate(5);
	while(nh.ok()){
		pub.publish(msg);
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}
