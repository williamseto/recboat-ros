#include <cmath>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

#include <sbpl/headers.h>

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "span_pose/span_pose.h"
#include "std_msgs/UInt8MultiArray.h"
#include <geometry_msgs/PoseStamped.h>


#include "navigation/nav_cmd.h"
#include "navigation/nav_wpt.h"

#include <tf/transform_datatypes.h>


#define WPT_IMMEDIATE     1  /* override current goal */
#define WPT_ADD           2  /* set goal or add to list */
#define WPT_CLEAR         3  /* clear list */


enum PlannerType
{
    INVALID_PLANNER_TYPE = -1,
    PLANNER_TYPE_ADSTAR,
    PLANNER_TYPE_ARASTAR,
    PLANNER_TYPE_PPCP,
    PLANNER_TYPE_RSTAR,
    PLANNER_TYPE_VI,
    PLANNER_TYPE_ANASTAR,

    NUM_PLANNER_TYPES
};

/* MAP CONSTANTS */

//double map_ref_x, map_ref_y, map_scale_x, map_scale_y;
//int map_pix_height;

double map_ref_x = 577336.797385;
double map_ref_y = 4484193.218161;
double map_scale_x = 4.997183;
double map_scale_y = 4.997080;
int map_pix_height = 2455;

///////////////////////////


visualization_msgs::Marker createPathMarker(string ns) {

    visualization_msgs::Marker marker;

    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = ns;
    marker.id = 0;

    // Set the marker type to our shape from earlier
    marker.type = visualization_msgs::Marker::LINE_STRIP;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = 0;
    marker.pose.position.y = 0;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 2.0;
    marker.scale.y = 2.0;
    marker.scale.z = 1.0;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 1.0f;
    marker.color.g = 0.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();
    return marker;
}

visualization_msgs::Marker createPointMarker(string ns) {
    visualization_msgs::Marker marker;

    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();
    marker.ns = ns;
    marker.action = visualization_msgs::Marker::ADD;

    marker.id = 0;
    marker.type = visualization_msgs::Marker::POINTS;

    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.scale.x = 0.5;
    marker.scale.y = 0.5;
    marker.scale.z = 0.01;

    marker.lifetime = ros::Duration();

    return marker;
}

visualization_msgs::Marker createBoatMarker(string ns) {
    visualization_msgs::Marker marker;

    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();
    marker.ns = ns;
    marker.action = visualization_msgs::Marker::ADD;

    marker.id = 0;
    marker.type = visualization_msgs::Marker::POINTS;

    marker.color.r = 0.0f;
    marker.color.g = 0.0f;
    marker.color.b = 1.0f;
    marker.color.a = 1.0;

    marker.scale.x = 3.0;
    marker.scale.y = 3.0;
    marker.scale.z = 0.01;

    marker.lifetime = ros::Duration();

    //add a point initially so later on, we just need to update the point
    geometry_msgs::Point p;
    p.x = 0.0;
    p.y = 0.0;
    p.z = 0.0;
    marker.points.push_back(p);

    return marker;
}

class PathPlanNode {

public:
    ros::Subscriber m_obstacleSub;
    ros::Subscriber m_poseSub;
    ros::Subscriber m_goalSub;
    ros::Publisher  m_pub;
    ros::Publisher  m_nav_cmd_pub;
    ros::Publisher  m_nav_wpt_pub;
    ros::NodeHandle m_nh;

    double m_boatX;
    double m_boatY;
    double m_boatYaw;
    double m_goalX;
    double m_goalY;
    double m_goalTheta;
    bool m_newgoal;

    EnvironmentNAVXYTHETALAT m_env;
    SBPLPlanner* m_planner;

    vector<int> m_solutionIDs;
    visualization_msgs::Marker m_pathMarker;
    visualization_msgs::Marker m_boatMarker;

    PathPlanNode() {
        m_obstacleSub = m_nh.subscribe("radar_obs", 1, &PathPlanNode::obstacleCB, this);
        m_poseSub = m_nh.subscribe("recboat/span_pose", 1, &PathPlanNode::poseCB, this);
        m_goalSub = m_nh.subscribe("move_base_simple/goal", 1, &PathPlanNode::goalCB, this);
        m_pub = m_nh.advertise<visualization_msgs::Marker>("visualization_marker_will", 5);

        m_nav_cmd_pub = m_nh.advertise<navigation::nav_cmd>("recboat/nav_cmd", 10);
        m_nav_wpt_pub = m_nh.advertise<navigation::nav_wpt>("recboat/nav_wpt", 100);

        m_planner = NULL;
        m_boatX = 1445;
        m_boatY = 1160;
        m_boatYaw = 0;

        m_goalX = 0;
        m_goalY = 0;
        m_goalTheta = 0;
        m_newgoal = false;

        m_pathMarker = createPathMarker("path");
        m_boatMarker = createBoatMarker("boat");

    }

    ~PathPlanNode() {
        delete m_planner;
    }

    void poseCB(const span_pose::span_pose &msg) {

        m_boatX = (msg.east - map_ref_x)/map_scale_x;
        m_boatY = map_pix_height + (msg.north - map_ref_y)/map_scale_y;
        m_boatYaw = msg.yaw;

    }

    void goalCB(const geometry_msgs::PoseStamped &msg) {

        //get yaw from 2d nav goal for path planner
        tf::Quaternion q(msg.pose.orientation.x,
                         msg.pose.orientation.y,
                         msg.pose.orientation.z,
                         msg.pose.orientation.w);
        tf::Matrix3x3 m(q);
        double roll, pitch, yaw;
        m.getRPY(roll, pitch, yaw);

        //printf("%f %f %f \n", roll, pitch, yaw);
        

        m_goalX = msg.pose.position.x;
        m_goalY = msg.pose.position.y;
        m_goalTheta = yaw;
        m_newgoal = true;
        //cout << msg.pose.position.x << endl;
    }

    void obstacleCB(const std_msgs::UInt8MultiArray &msg) {

    }

    int ros_nav_cmd(int cmd)
    {
      navigation::nav_cmd msg;

      msg.cmd = cmd;
      m_nav_cmd_pub.publish(msg);

      return(0);
    }

    int ros_nav_wpt(double north, double east, float vel, int action)
    {
      navigation::nav_wpt msg;

      msg.north = north;
      msg.east = east;
      msg.vel = vel;
      msg.action = action;

      m_nav_wpt_pub.publish(msg);

      return(0);
    }

    void initializeEnv(char* envCfgFilename, char* motPrimFilename) {
        // set the perimeter of the robot
        // it is given with 0, 0, 0 robot ref. point for which planning is done.
        vector<sbpl_2Dpt_t> perimeterptsV;
        sbpl_2Dpt_t pt_m;
        double halfwidth = 0.01;
        double halflength = 0.01;
        pt_m.x = -halflength;
        pt_m.y = -halfwidth;
        perimeterptsV.push_back(pt_m);
        pt_m.x = halflength;
        pt_m.y = -halfwidth;
        perimeterptsV.push_back(pt_m);
        pt_m.x = halflength;
        pt_m.y = halfwidth;
        perimeterptsV.push_back(pt_m);
        pt_m.x = -halflength;
        pt_m.y = halfwidth;
        perimeterptsV.push_back(pt_m);

        if (!m_env.InitializeEnv(envCfgFilename, perimeterptsV, motPrimFilename)) {
            printf("ERROR: InitializeEnv failed\n");
            throw SBPL_Exception();
        }

    }

    void initializePlanner() {

        double initialEpsilon = 3.0;
        bool bsearchuntilfirstsolution = false;
        bool bforwardsearch = false;

        m_planner = new ARAPlanner(&m_env, bforwardsearch);
 


        //get start and goal from env
        MDPConfig MDPCfg;

        // initialize MDP info
        if (!m_env.InitializeMDPCfg(&MDPCfg)) {
            printf("ERROR: InitializeMDPCfg failed\n");
            throw new SBPL_Exception();
        }
        // set planner properties
        if (m_planner->set_start(MDPCfg.startstateid) == 0) {
            printf("ERROR: failed to set start state\n");
            throw new SBPL_Exception();
        }
        if (m_planner->set_goal(MDPCfg.goalstateid) == 0) {
            printf("ERROR: failed to set goal state\n");
            throw new SBPL_Exception();
        }
        m_planner->set_initialsolution_eps(initialEpsilon);
        m_planner->set_search_mode(bsearchuntilfirstsolution);


    }

    int runPlannerOnce() {

        //scale start & goal according to resolution of map
        //currently hard-coded to 5 meters per pixel
        double startx = m_boatX * 5;
        double starty = m_boatY * 5;

        double goalx = m_goalX * 5;
        double goaly = m_goalY * 5;

        //convert from heading to (x,y,theta) convention
        double starttheta = (m_boatYaw - M_PI/2) * -1;
        
        //printf("%f %f %f\n", m_boatX, m_boatY, m_boatYaw);

        int newstartstateID = m_env.SetStart(startx, starty, starttheta);
        int newgoalstateID = m_env.SetGoal(goalx, goaly, m_goalTheta);


        // update the planner
        if (m_planner->set_start(newstartstateID) == 0) {
            printf("ERROR: failed to update robot pose in the planner\n");
            throw new SBPL_Exception();
        }

        if (m_planner->set_goal(newgoalstateID) == 0) {
            printf("ERROR: failed to update robot pose in the planner\n");
            throw new SBPL_Exception();
        }

        // plan a path, and save in member variable

        printf("new planning...\n");

        int bret = m_planner->replan(60.0, &m_solutionIDs);

        return bret;

    }

    void runPlanner() {
        /*
        will continuously replan the path, based on current position and 
        any updated obstacles.

        TODO: get obstacles from radar data
        */

        double goaltol_x = 0.001, goaltol_y = 0.001, goaltol_theta = 0.001;

        double allocated_time_secs_foreachplan = 10.0; // in seconds

        visualization_msgs::Marker path_marker = createPathMarker("path");
        visualization_msgs::Marker boat_marker = createBoatMarker("boat");
        visualization_msgs::Marker obs_marker = createPointMarker("obstacles");


        vector<int> preds_of_changededgesIDV;
        vector<nav2dcell_t> changedcellsV;
        nav2dcell_t nav2dcell;
        vector<sbpl_xy_theta_pt_t> xythetaPath;

        vector<int> solution_stateIDs_V;

        // environment parameters
        int size_x = -1, size_y = -1, num_thetas = -1;
        double startx = -1, starty = -1, starttheta = -1;
        double goalx = -1, goaly = -1, goaltheta = -1;
        double cellsize_m = 0.0, nominalvel_mpersecs = 0.0, timetoturn45degsinplace_secs = 0.0;
        unsigned char obsthresh = 0;
        vector<SBPL_xytheta_mprimitive> motionprimitiveV;

        // additional environment parameters
        unsigned char costinscribed_thresh = 0;
        unsigned char costcircum_thresh = 0;

        // get environment parameters from the environment
        m_env.GetEnvParms(&size_x, &size_y, &num_thetas, &startx, &starty, &starttheta, &goalx,
                          &goaly, &goaltheta, &cellsize_m, &nominalvel_mpersecs,
                          &timetoturn45degsinplace_secs, &obsthresh, &motionprimitiveV);

        // now comes the main loop
        while (fabs(startx - goalx) > goaltol_x || fabs(starty - goaly) > goaltol_y ) {

        
            // sensor data update
            bool bChanges = false;
            preds_of_changededgesIDV.clear();
            changedcellsV.clear();

            //radar obstacle data update

            double TimeStarted = clock();

            // if necessary notify the planner of changes to costmap
            if (bChanges) {
                if (dynamic_cast<ARAPlanner*> (m_planner) != NULL) {
                    ((ARAPlanner*)m_planner)->costs_changed(); //use by ARA* planner (non-incremental)
                }
                else if (dynamic_cast<ADPlanner*> (m_planner) != NULL) {
                    // get the affected states
                    m_env.GetPredsofChangedEdges(&changedcellsV, &preds_of_changededgesIDV);
                    // let know the incremental planner about them
                    //use by AD* planner (incremental)
                    ((ADPlanner*)m_planner)->update_preds_of_changededges(&preds_of_changededgesIDV); 
                    printf("%d states were affected\n", (int)preds_of_changededgesIDV.size());
                }
            }

            //pose update

            // update the environment

            //scale to cellsize
            startx = m_boatX * 5;
            starty = m_boatY * 5;

            //convert from heading to (x,y,theta) convention
            starttheta = (m_boatYaw - M_PI/2) * -1;
            //printf("%f %f %f\n", startx, starty, starttheta);
            printf("%f %f %f\n", m_boatX, m_boatY, m_boatYaw);

            int newstartstateID = m_env.SetStart(startx, starty, starttheta);


            // update the planner
            if (m_planner->set_start(newstartstateID) == 0) {
                printf("ERROR: failed to update robot pose in the planner\n");
                throw new SBPL_Exception();
            }

            // plan a path
            bool bPlanExists = false;

            printf("new planning...\n");
            bPlanExists = (m_planner->replan(allocated_time_secs_foreachplan, &solution_stateIDs_V) == 1);
            printf("done with the solution of size=%d and sol. eps=%f\n", (unsigned int)solution_stateIDs_V.size(),
                   m_planner->get_solution_eps());
            m_env.PrintTimeStat(stdout);

            /*
            // write the solution to sol.txt
            fprintf(fSol, "plan time=%.5f eps=%.2f\n", (clock() - TimeStarted) / ((double)CLOCKS_PER_SEC),
                    planner->get_solution_eps());
            fflush(fSol);

            xythetaPath.clear();
            environment_navxythetalat.ConvertStateIDPathintoXYThetaPath(&solution_stateIDs_V, &xythetaPath);
            printf("actual path (with intermediate poses) size=%d\n", (unsigned int)xythetaPath.size());
            for (unsigned int i = 0; i < xythetaPath.size(); i++) {
                fprintf(fSol, "%.3f %.3f %.3f\n", xythetaPath.at(i).x, xythetaPath.at(i).y, xythetaPath.at(i).theta);
            }
            fprintf(fSol, "*********\n");
            */

            path_marker.points.clear();

            boat_marker.points.clear();

            // marker for the boat's location

            geometry_msgs::Point p;
            p.x = m_boatX;
            p.y = m_boatY;
            p.z = 0.0;
            boat_marker.points.push_back(p);
            path_marker.points.push_back(p);

            if (bPlanExists) {

                
                for (int j = 1; j < (int)solution_stateIDs_V.size(); j++) {
                    int newx, newy, newtheta = 0;
                    m_env.GetCoordFromState(solution_stateIDs_V[j], newx, newy, newtheta);

                    //fprintf(fSol, "%d %d %d\n", newx, newy, newtheta);


                    //visualize path
                    geometry_msgs::Point p;
                    p.x = newx;
                    p.y = newy;
                    p.z = 0.0;
                    path_marker.points.push_back(p);


                }
            }
            //fflush(fSol);


            //obs_marker.points.clear();
            /*
            boat_marker.points.clear();

            // marker for the boat's location

            geometry_msgs::Point p;
            p.x = m_boatX;
            p.y = m_boatY;
            p.z = 0.0;
            boat_marker.points.push_back(p);
            */

            m_pub.publish(path_marker);
            m_pub.publish(boat_marker);
            //marker_pub.publish(obs_marker);


            // move along the path
            if (bPlanExists && (int)xythetaPath.size() > 1) {
                //get coord of the successor
                int newx, newy, newtheta;

                // move until we move into the end of motion primitive
                //environment_navxythetalat.GetCoordFromState(solution_stateIDs_V[1], newx, newy, newtheta);

                //printf("moving from %d %d %d to %d %d %d\n", startx_c, starty_c, starttheta_c, newx, newy, newtheta);



                // move- send commands to boat?

            } else {
                printf("No move is made\n");
            }

            //ros::Duration(3.0).sleep();
            ros::spinOnce();
        }
    }

    void visualize() {
        m_boatMarker.points[0].x = m_boatX;
        m_boatMarker.points[0].y = m_boatY;


        //visualize path
        //add current position as first point

        m_pathMarker.points.clear();

        /*
        geometry_msgs::Point p;
        p.x = m_boatX;
        p.y = m_boatY;
        p.z = 0.0;
        m_pathMarker.points.push_back(p);
        */

        for (int j = 0; j < (int)m_solutionIDs.size(); j++) {
            int newx, newy, newtheta = 0;
            m_env.GetCoordFromState(m_solutionIDs[j], newx, newy, newtheta);

            //visualize path
            geometry_msgs::Point p;
            p.x = newx;
            p.y = newy;
            p.z = 0.0;
            m_pathMarker.points.push_back(p);
        }

        m_pub.publish(m_boatMarker);
        m_pub.publish(m_pathMarker);

    
    }

};


int main(int argc, char** argv)
{
  
  ros::init(argc, argv, "ppnode");


  PathPlanNode ppt;
  ppt.initializeEnv(argv[1], argv[2]);
  ppt.initializePlanner();

  //ppt.runPlanner();

  ros::Rate r(1);


  while(ros::ok()) {


    if(ppt.m_newgoal) {
        int bret = ppt.runPlannerOnce();

        if (bret) {

            //clear waypoints before sending
            ppt.ros_nav_wpt(0.0, 0.0, 0.0, WPT_CLEAR);

            for (int j = 1; j < (int)ppt.m_solutionIDs.size(); j++) {
                int newx, newy, newtheta = 0;
                ppt.m_env.GetCoordFromState(ppt.m_solutionIDs[j], newx, newy, newtheta);


                //send waypoints
                double test_east = (newx * map_scale_x) + map_ref_x;
                double test_north = ((newy - map_pix_height) * map_scale_y) + map_ref_y;
                ppt.ros_nav_wpt(test_north, test_east, 0.1, WPT_ADD);
            }

            usleep(100000);
            ppt.ros_nav_cmd(3);
        }
        ppt.m_newgoal = false;
        
    }

    ppt.visualize();

    

    ros::spinOnce();
    r.sleep();
  }



  //ros::spin();
  return 0;
}