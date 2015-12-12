/*
Waypoint Follower 
Reads waypoints from a text file
converts them in UTM coordinates
sends UTM coordinate to low level controller to run the boat
tchugh@cmu.edu
*/

#include<iostream>
#include "ros_comm.h"
#include "path.h"
#include <unistd.h>
#include <pthread.h>
#include <assert.h>
#include <vector>
//File Handling
#include <fstream>

#include <algorithm>

using namespace std;

#define WPT_IMMEDIATE     1  /* override current goal */
#define WPT_ADD           2  /* set goal or add to list */
#define WPT_CLEAR         3  /* clear list */

static int nav_paused = 0;

extern struct path_type *wpt_path;
struct ros_pose_status cur_pose_status;

static pthread_t ros_pthread;

//structure for x,y pixel coordinate
struct coordinate
{
  int x;
  int y;
};

//Stucture for UTM coordinates
struct UTMcoordinate
{
  double east;
  double north;
};

//Function Declations

//Read pixel coordinates from file
vector <coordinate> readCoordinates();

//Function to add the waypoints to the list
void addwaypoints(double, double, bool);

//Clear all existing waypoints
void clearwaypoints();

//Starts the navigation
void startnavigation();

void addcoordinates(vector <coordinate>);

UTMcoordinate convertPixelUTM (int,int);

//Main Function
int main(int argc, char** argv)
{

  pthread_attr_t pattr;
  ros_init(&argc, &argv); 
  usleep(100000);
  pthread_create(&ros_pthread, NULL, ros_thread, NULL);
  usleep(100000);
  //Read pixel coordinates  
  vector <coordinate> coordinates = readCoordinates();
  cout << "\n Number of Coordinates: "<< coordinates.size();
  reverse(coordinates.begin(),coordinates.end());
  addcoordinates(coordinates);
  
  //addwaypoints(-15.8807082222,-9.95340152922);
  //addwaypoints(-40.4,79.9);
  usleep(100000);
  startnavigation();
 // clearwaypoints();

}

//Take pixels as input
//return UTMcoordinates
UTMcoordinate convertPixelUTM (int x, int y)
{

    UTMcoordinate UTMvalue;
   //east
    //Get this value from the world file
    double ori_UTMeast = 582862.554791;
    //north
    double ori_UTMnorth = 4479880.713762;
    // meters/pixel
    double grid_size = 5.082;
    //Image height 
    double map_height = 787;

    //Converting Pixels to UTM
    UTMvalue.east = map_height  + (ori_UTMeast - x)/grid_size;
    UTMvalue.north = (ori_UTMnorth - y)/grid_size;

    return UTMvalue;
}

//Add the coordinates to the path
void addcoordinates(vector <coordinate> coordinates)
{
  int i = 0;
    while (i < coordinates.size())
    {
      UTMcoordinate UTMvalue = convertPixelUTM(coordinates[i].x, coordinates[i].y);
      if (i == coordinates.size()-1)
      addwaypoints(UTMvalue.east,UTMvalue.north, true);
      else
      addwaypoints(UTMvalue.east,UTMvalue.north, false);
      ++i;
    }
}

//Function to read coordinates from file
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

//Function to add the waypoints to the list

void addwaypoints(double UTMeast, double UTMwest, bool islast)
{
   cout<<"\nAdding waypoints main";
   pathwin_add_wpt(UTMeast, UTMwest);
   if(islast)
   pathwin_add_wpt(cur_pose_status.east, cur_pose_status.north);
}

//Clear all existing waypoints
void clearwaypoints()
{
   cout<<"\nClearing waypoints main";
   ros_nav_wpt(0.0, 0.0, 0.0, WPT_CLEAR);
   pathwin_clear_wpt();
}

//Starts the navigation
void startnavigation()
{
       cout<<"\nstart...";
       /* only resend waypoints for fresh start */
       if (!nav_paused) {
         cout<<"\nsending waypoints...";
         ros_nav_wpt(0.0, 0.0, 0.0, WPT_CLEAR);
         if (!wpt_path || !wpt_path->npts) return;

         float vel = 0.15;
       
         for (int i = 0; i < wpt_path->npts; i++) {
           cout<<"\nNumber of waypoints"<< wpt_path->npts;
           ros_nav_wpt(wpt_path->y[i], wpt_path->x[i], vel, WPT_ADD);
         }
       }
       nav_paused = 0;
       usleep(100000);
       ros_nav_cmd(3);
}