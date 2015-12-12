
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
//File Handling
#include <fstream>
#include <vector>
#include "std_msgs/String.h"
//Included for publishing message
#include "publish_path/publish_path.h"
//Thread sleep
#include <unistd.h>

using namespace std;

//Publsiher obsject
ros::Publisher path_pub;

//structure to store x,y coordinate
struct coordinate
{
	int x;
	int y;
};

//Function Declations
vector <coordinate> readCoordinates();
int ros_pub_path(int x, int y);

//Main Function
int main(int argc, char **argv)
{
//Creating object of the message	
   publish_path::publish_path msg;
	
//Read pixel coordinates	
  vector <coordinate> coordinates = readCoordinates();

//Initiate ROS node
  ros::init(argc, argv, "recboat_path");

//ROS Node handler
  ros::NodeHandle n;

//Defining Publisher
  path_pub = n.advertise<publish_path::publish_path>("publish_path", 1000);

//Publishing coordinates as ROS message after x time interval
  int count = 0;
  while (count < coordinates.size())
  {
	 ros_pub_path(coordinates[count].x, coordinates[count].y);
	 cout <<"\npublishing";
   usleep(500000);
   ++count;
  }


  return 0;
}

//Function to read pixel coordinates from file
//Returns vector of type coordinate which is a struct of int x and int y
vector <coordinate> readCoordinates()
{
    //Vector of coordinates
     vector<coordinate> coordinates; 

    //Open the file
    //Put the file where exe of this package is getting generate
    //or Change the path
	std::fstream myfile("sol.txt.discrete", std::ios_base::in);
    
    cout<<"\nreading File";
   
    int a;
    //Create the object to the structure 
    coordinate coordinateobj;

    //Read till the end of the file
    //File has 3 numbers in a row
    //First is x coordinate of pixel
    //second one is y coordinate
    //Third is the heading
    while (myfile >> a)
    {   	
    	//Reding first coordinate
      coordinateobj.x = a;
      //Reading second coordinate
      myfile >> a;
      coordinateobj.y = a;
      //Ignoring third coordinate for now
      myfile >> a;
        
      //Storing the coordinates in the vector	
      coordinates.push_back(coordinateobj);
        
    }

  //Printing the coordinates
  for (int i =0; i< coordinates.size();i++)
  {
  	cout << "\n"<<coordinates[i].x<<" "<<coordinates[i].y;
  }

return coordinates;

}

//Publish the message
int ros_pub_path(int x, int y)
{
  publish_path::publish_path msg;

  msg.x = x;
  msg.y = y;

  path_pub.publish(msg);

  return(0);
}
