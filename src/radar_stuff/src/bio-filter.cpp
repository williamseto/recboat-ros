
/****************lalala*********************/
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include "std_msgs/UInt8MultiArray.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include "std_msgs/Float64.h"
#include "std_msgs/Float32.h"
#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <sensor_msgs/image_encodings.h>
#include <boost/math/distributions/binomial.hpp>
#include <algorithm>



using namespace std;
using namespace boost::math;

typedef unsigned long long timestamp_t;

static timestamp_t get_timestamp () {
  struct timeval now;
  gettimeofday (&now, NULL);
  return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}


class bi_filter
{
// Member Variables
private:
  ros::NodeHandle n;
  
  
// Member Functions
public:
  
  ros::Subscriber sub;
  ros::Publisher pub;
  

  double spoke_n;
  double occupied_p;
  double P_thresh;
  double raw_thresh;


  bi_filter()
  {
    spoke_n    = 16;    //ideally should be beamwidth / (360/2048)
    occupied_p = 0.5;   //prob. that a cell is occupied (used for the bino. distribution)
    P_thresh   = 0.95;  //threshold for binomial cdf
    raw_thresh = 0;     //threshold for the raw cell value (0-255) to be considered occupied

    sub = n.subscribe("raw_radar_image", 10, &bi_filter::Callback, this);
    pub = n.advertise<std_msgs::UInt8MultiArray>("filtered_radar_image", 1);

  }  
  
  void Callback(const std_msgs::UInt8MultiArray &msg)
    {
      //cout<<"enter Callback"<<endl;

      timestamp_t t0 = get_timestamp();

      // change msg to 2d array
      std_msgs::UInt8MultiArray filtered_data_msg;

      int reshaped_data[2048][512];

      int x=0;
      int y=0;
    	
      /*
    	for (int i=0; i<2048*512; i++)
      {
          x = i%2048;
          if (i==2048) y++;

          //cout << int(msg.data[i]) << endl;
          reshaped_data[x][y] = int(msg.data[i]);


      }
      */

      for (int j=0; j<512; j++)     
      {
          for (int i=0; i<2048; i++)
          {  
              reshaped_data[i][j] = int(msg.data[j*2048+i]);
          }
      }
      //cout<<"reshape done"<<endl;

      uint8_t filtered_data[2048*512] = {0};
      double P = 0.0;

      #pragma omp parallel for
      for (int j=0; j<512; j++)     
      {
          for (int i=0; i<2048; i++)
          {  

            int m = 0;

            for (int l=-spoke_n/2; l<spoke_n/2; l++)
            { 
              int check_x = (i+l)%2048;
              int check_y = j;

              //int check_x = i;
              //int check_y = (j+l)%2048;
              //cout<<"check data: "<<reshaped_data[check_x][check_y]<<endl;

              if (reshaped_data[check_x][check_y]>raw_thresh)
                m++;
            }


            
            //for (int k=0; k<m; k++)
            //{
            //  P = P + cdf(binomial(spoke_n, occupied_p),k);
            //}

            P = cdf(binomial(spoke_n, occupied_p),m);
            

            
            if (P >= P_thresh) {
              filtered_data[j*2048+i] = 255;
            } else {
              filtered_data[j*2048+i] = 0;
            }
            
            //filtered_data[j*2048+i] = reshaped_data[i][j];
            //filtered_data[j*2048+i] = int(msg.data[j*2048+i]);

            
            
          }
      }
      

      filtered_data_msg.data.insert(filtered_data_msg.data.end(), &filtered_data[0], &filtered_data[2048*512]);
    	pub.publish(filtered_data_msg);

      timestamp_t t1 = get_timestamp();

      cout << (t1 - t0) << endl;

  }
};

int main(int argc, char** argv)
{
  
  ros::init(argc, argv, "filter");
  bi_filter bf;
  ros::spin();
  return 0;
}
