#include "markerrviz.h"
#include "boatlocation.h"
#include "environmentriver.h"
#include "pathplanner.h"
#include "lowlevelcontroller.h"
#include <ros/ros.h>
#include <sbpl/headers.h>

#define WPT_IMMEDIATE     1  /* override current goal */
#define WPT_ADD           2  /* set goal or add to list */
#define WPT_CLEAR         3  /* clear list */

int main(int argc, char ** argv)
{ 
    ros::init(argc,argv,"pptest");
    ros::NodeHandle nodeHandle;
    
    /////////////Initialize LowlevelController//////////////
    LowlevelController lowlevelcontroller(&nodeHandle);
    //////////////////////////
    
    /////////////Initialize Marker/////////////////
    MarkerType markerType = POINTS;
    MarkerRVIZ *markerObj = new MarkerRVIZ(&nodeHandle, "pptest_green", "map", markerType, 1.0f, 0.0f, 0.0f);
    
    MarkerType markerType1 = POINTS;
    MarkerRVIZ *markerObj1 = new MarkerRVIZ(&nodeHandle, "pptest_red", "map", markerType1, 0.0f, 1.0f,0.0f);
    
    MarkerType markerType2 = LINE_STRIP;
    MarkerRVIZ *markerObj2 = new MarkerRVIZ(&nodeHandle, "pptest_blue", "map", markerType2, 0.0f, 0.0f, 1.0f);
    ///////////////////////////////////////
    
    //////////Initialize Environment//////////
    EnvironmentRiver environmentRiver;
    environmentRiver.initializeEnv(argv[1], argv[2]);
    /////////////////////////////////////////
    
    ////////////Initialize Path Planner/////////////
    PathPlanner pathplanner;
    pathplanner.initializePlanner(&environmentRiver.m_env);
    ////////////////////
    
    ///////////////Initialize Boat Location and Goal////////////////
    BoatLocation *boatLocation = new BoatLocation(&nodeHandle, 577336.797385,4484193.218161, 4.997183, 4.997080, 2455); 
    ///////////////////////////////
   
    ros::Rate r(5);
    
  
    while (ros::ok())
    {
        BoatPosition boatPosition = boatLocation->getPosition();
        BoatGoal boatGoal = boatLocation->getGoal();
        if (boatGoal.m_newgoal)
        {   
            std::cout << "\nGot new goal";        
            
            int bret = pathplanner.runPlannerOnce(&environmentRiver.m_env, boatPosition, boatGoal);
            
            if (bret) 
            {
                std::cout <<"\nBret is true";
                lowlevelcontroller.ros_nav_wpt(0.0, 0.0, 0.0, WPT_CLEAR);
                markerObj2->ClearMarker();
                for (int j = 1; j < (int)pathplanner.m_solutionIDs.size(); j++) 
                {
                        int newx, newy, newtheta = 0;
                        environmentRiver.m_env.GetCoordFromState(pathplanner.m_solutionIDs[j], newx, newy, newtheta);

                        //send waypoints
                        double test_east = (newx * boatLocation->mapreference.map_scale_x) + boatLocation->mapreference.map_ref_x;
                        double test_north = ((newy - boatLocation->mapreference.map_pix_height) * boatLocation->mapreference.map_scale_y) + boatLocation->mapreference.map_ref_y;
                        lowlevelcontroller.ros_nav_wpt(test_north, test_east, 0.1, WPT_ADD);                        
                        //visualize path
                        markerObj2->UpdateGUI(newx, newy, newtheta);
                }
            }
           boatLocation->setGoalFalse();
        }
        
        if(boatPosition.m_boatX != 0 && boatPosition.m_boatY != 0)
        {
         markerObj->UpdateGUI(boatPosition.m_boatX, boatPosition.m_boatY, boatPosition.m_boatYaw);
         markerObj1->ClearMarker();
         markerObj1->UpdateGUI(boatPosition.m_boatX, boatPosition.m_boatY, boatPosition.m_boatYaw);        
         //std::cout<<"\nUpdating GUI\n"<<"X: "<<boatPosition.m_boatX<<" Y: "<<boatPosition.m_boatY<<" Z: "<<boatPosition.m_boatYaw;
        }
         ros::spinOnce();
         r.sleep();
    }
    return 0;
}

