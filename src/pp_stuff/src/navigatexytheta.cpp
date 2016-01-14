/*******************************************************************************
 * planandnavigatexythetalat
 * @brief An example simulation of how a robot would use (x,y,theta) lattice
 *        planning.
 *
 * @param envCfgFilename The environment config file. See
 *                       sbpl/env_examples/nav3d/ for examples
 *******************************************************************************/


#include <cmath>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

#include <sbpl/headers.h>

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

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
    marker.scale.x = 0.05;
    marker.scale.y = 0.05;
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

    marker.scale.x = 1.0;
    marker.scale.y = 1.0;
    marker.scale.z = 0.01;

    marker.lifetime = ros::Duration();
    return marker;
}


int planandnavigatexythetalat(PlannerType plannerType, char* envCfgFilename, char* motPrimFilename, bool forwardSearch, int argc, char *argv[])
{
    ros::init(argc, argv, "ppt");
    ros::NodeHandle n;
    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 5);

    visualization_msgs::Marker path_marker = createPathMarker("path");
    visualization_msgs::Marker boat_marker = createBoatMarker("boat");
    visualization_msgs::Marker obs_marker = createPointMarker("obstacles");

    //WHAT IS BFORWARDSEARCH???

    int dummy;

    double allocated_time_secs_foreachplan = 10.0; // in seconds
    double initialEpsilon = 3.0;
    bool bsearchuntilfirstsolution = false;
    bool bforwardsearch = forwardSearch;

    double goaltol_x = 0.001, goaltol_y = 0.001, goaltol_theta = 0.001;

    bool bPrint = true;
    bool bPrintMap = true;

    EnvironmentNAVXYTHETALAT environment_navxythetalat;
    EnvironmentNAVXYTHETALAT trueenvironment_navxythetalat;

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

    //	perimeterptsV.clear();

    // initialize true map from the environment file without perimeter or motion primitives
    if (!trueenvironment_navxythetalat.InitializeEnv(envCfgFilename)) {
        printf("ERROR: InitializeEnv failed\n");
        throw new SBPL_Exception();
    }

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

    // get environment parameters from the true environment
    trueenvironment_navxythetalat.GetEnvParms(&size_x, &size_y, &num_thetas, &startx, &starty, &starttheta, &goalx,
                                              &goaly, &goaltheta, &cellsize_m, &nominalvel_mpersecs,
                                              &timetoturn45degsinplace_secs, &obsthresh, &motionprimitiveV);
    costinscribed_thresh = trueenvironment_navxythetalat.GetEnvParameter("cost_inscribed_thresh");
    costcircum_thresh = trueenvironment_navxythetalat.GetEnvParameter("cost_possibly_circumscribed_thresh");

    // print the map
    if (bPrintMap) {
        printf("true map:\n");
        for (int y = 0; y < size_y; y++) {
            for (int x = 0; x < size_x; x++) {
                printf("%3d ", trueenvironment_navxythetalat.GetMapCost(x, y));
            }
            printf("\n");
        }
        printf("System Pause (return=%d)\n", system("pause"));
    }

    // create an empty map
    unsigned char* map = new unsigned char[size_x * size_y];
    for (int i = 0; i < size_x * size_y; i++) {
        map[i] = 0;
    }

    // check the start and goal obtained from the true environment
    printf("start: %f %f %f, goal: %f %f %f\n", startx, starty, starttheta, goalx, goaly, goaltheta);

    // set robot environment parameters (should be done before initialize function is called)
    if (!environment_navxythetalat.SetEnvParameter("cost_inscribed_thresh", costinscribed_thresh)) {
        printf("ERROR: failed to set parameters\n");
        throw new SBPL_Exception();
    }
    if (!environment_navxythetalat.SetEnvParameter("cost_possibly_circumscribed_thresh", costcircum_thresh)) {
        printf("ERROR: failed to set parameters\n");
        throw new SBPL_Exception();
    }

    // initialize environment (should be called before initializing anything else)
    EnvNAVXYTHETALAT_InitParms params;
    params.startx = startx;
    params.starty = starty;
    params.starttheta = starttheta;
    params.goalx = goalx;
    params.goaly = goaly;
    params.goaltheta = goaltheta;
    params.goaltol_x = goaltol_x;
    params.goaltol_y = goaltol_y;
    params.goaltol_theta = goaltol_theta;
    params.mapdata = map;
    params.numThetas = num_thetas;

    bool envInitialized = environment_navxythetalat.InitializeEnv(size_x, size_y, perimeterptsV, cellsize_m,
                                                                  nominalvel_mpersecs, timetoturn45degsinplace_secs,
                                                                  obsthresh, motPrimFilename, params);

    if (!envInitialized) {
        printf("ERROR: InitializeEnv failed\n");
        throw new SBPL_Exception();
    }

    // set start and goal states
    environment_navxythetalat.SetStart(startx, starty, starttheta);
    environment_navxythetalat.SetGoal(goalx, goaly, goaltheta);

    MDPConfig MDPCfg;

    // initialize MDP info
    if (!environment_navxythetalat.InitializeMDPCfg(&MDPCfg)) {
        printf("ERROR: InitializeMDPCfg failed\n");
        throw new SBPL_Exception();
    }

    // create a planner
    vector<int> solution_stateIDs_V;

    SBPLPlanner* planner = NULL;
    switch (plannerType) {
    case PLANNER_TYPE_ARASTAR:
        printf("Initializing ARAPlanner...\n");
        planner = new ARAPlanner(&environment_navxythetalat, bforwardsearch);
        break;
    case PLANNER_TYPE_ADSTAR:
        printf("Initializing ADPlanner...\n");
        planner = new ADPlanner(&environment_navxythetalat, bforwardsearch);
        break;
    case PLANNER_TYPE_RSTAR:
        printf("Invalid configuration: xytheta environment does not support rstar planner...\n");
        return 0;
    case PLANNER_TYPE_ANASTAR:
        printf("Initializing anaPlanner...\n");
        planner = new anaPlanner(&environment_navxythetalat, bforwardsearch);
        break;
    default:
        printf("Invalid planner type\n");
        break;
    }

    // set the start and goal states for the planner and other search variables
    if (planner->set_start(MDPCfg.startstateid) == 0) {
        printf("ERROR: failed to set start state\n");
        throw new SBPL_Exception();
    }
    if (planner->set_goal(MDPCfg.goalstateid) == 0) {
        printf("ERROR: failed to set goal state\n");
        throw new SBPL_Exception();
    }
    planner->set_initialsolution_eps(initialEpsilon);
    planner->set_search_mode(bsearchuntilfirstsolution);

    // compute sensing as a square surrounding the robot with length twice that of the
    // longest motion primitive
    vector<sbpl_2Dcell_t> sensecells;
    double maxMotPrimLengthSquared = 0.0;
    double maxMotPrimLength = 0.0;
    const EnvNAVXYTHETALATConfig_t* cfg = environment_navxythetalat.GetEnvNavConfig();
    for (int i = 0; i < (int)cfg->mprimV.size(); i++) {
        const SBPL_xytheta_mprimitive& mprim = cfg->mprimV.at(i);
        int dx = mprim.endcell.x;
        int dy = mprim.endcell.y;
        if (dx * dx + dy * dy > maxMotPrimLengthSquared) {
            std::cout << "Found a longer motion primitive with dx = " << dx << " and dy = " << dy
                << " from starttheta = " << (int)mprim.starttheta_c << std::endl;
            maxMotPrimLengthSquared = dx * dx + dy * dy;
        }
    }
    maxMotPrimLength = sqrt((double)maxMotPrimLengthSquared);
    std::cout << "Maximum motion primitive length: " << maxMotPrimLength << std::endl;

    //int sensingRange = (int)ceil(maxMotPrimLength);
    int sensingRange = 2;
    for (int x = -sensingRange; x <= sensingRange; x++) {
        for (int y = -sensingRange; y <= sensingRange; y++) {
            sensecells.push_back(sbpl_2Dcell_t(x, y));
        }
    }

    // create a file to hold the solution vector
    const char* sol = "sol.txt";
    FILE* fSol = fopen(sol, "w");
    if (fSol == NULL) {
        printf("ERROR: could not open solution file\n");
        throw new SBPL_Exception();
    }

    // print the goal pose
    int goalx_c = CONTXY2DISC(goalx, cellsize_m);
    int goaly_c = CONTXY2DISC(goaly, cellsize_m);
    int goaltheta_c = ContTheta2Disc(goaltheta, num_thetas);
    printf("goal_c: %d %d %d\n", goalx_c, goaly_c, goaltheta_c);

    vector<int> preds_of_changededgesIDV;
    vector<nav2dcell_t> changedcellsV;
    nav2dcell_t nav2dcell;
    vector<sbpl_xy_theta_pt_t> xythetaPath;

    // now comes the main loop
    while (fabs(startx - goalx) > goaltol_x || fabs(starty - goaly) > goaltol_y || fabs(starttheta - goaltheta)
        > goaltol_theta) {

        
        //simulate sensor data update
        bool bChanges = false;
        preds_of_changededgesIDV.clear();
        changedcellsV.clear();

        // simulate sensing the cells
        for (int i = 0; i < (int)sensecells.size(); i++) {
            int x = CONTXY2DISC(startx, cellsize_m) + sensecells.at(i).x;
            int y = CONTXY2DISC(starty, cellsize_m) + sensecells.at(i).y;

            // ignore if outside the map
            if (x < 0 || x >= size_x || y < 0 || y >= size_y) {
                continue;
            }

            int index = x + y * size_x;
            unsigned char truecost = trueenvironment_navxythetalat.GetMapCost(x, y);
            // update the cell if we haven't seen it before
            if (map[index] != truecost) {
                map[index] = truecost;
                environment_navxythetalat.UpdateCost(x, y, map[index]);
                printf("setting cost[%d][%d] to %d\n", x, y, map[index]);
                bChanges = true;
                // store the changed cells
                nav2dcell.x = x;
                nav2dcell.y = y;
                changedcellsV.push_back(nav2dcell);
            }
        }

        double TimeStarted = clock();

        // if necessary notify the planner of changes to costmap
        if (bChanges) {
            if (dynamic_cast<ARAPlanner*> (planner) != NULL) {
                ((ARAPlanner*)planner)->costs_changed(); //use by ARA* planner (non-incremental)
            }
            else if (dynamic_cast<ADPlanner*> (planner) != NULL) {
                // get the affected states
                environment_navxythetalat.GetPredsofChangedEdges(&changedcellsV, &preds_of_changededgesIDV);
                // let know the incremental planner about them
                //use by AD* planner (incremental)
                ((ADPlanner*)planner)->update_preds_of_changededges(&preds_of_changededgesIDV); 
                printf("%d states were affected\n", (int)preds_of_changededgesIDV.size());
            }
        }

        int startx_c = CONTXY2DISC(startx, cellsize_m);
        int starty_c = CONTXY2DISC(starty, cellsize_m);
        int starttheta_c = ContTheta2Disc(starttheta, num_thetas);

        // plan a path
        bool bPlanExists = false;

        printf("new planning...\n");
        bPlanExists = (planner->replan(allocated_time_secs_foreachplan, &solution_stateIDs_V) == 1);
        printf("done with the solution of size=%d and sol. eps=%f\n", (unsigned int)solution_stateIDs_V.size(),
               planner->get_solution_eps());
        environment_navxythetalat.PrintTimeStat(stdout);

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

        path_marker.points.clear();
        for (int j = 1; j < (int)solution_stateIDs_V.size(); j++) {
            int newx, newy, newtheta = 0;
            environment_navxythetalat.GetCoordFromState(solution_stateIDs_V[j], newx, newy, newtheta);
            fprintf(fSol, "%d %d %d\n", newx, newy, newtheta);


            //visualize path
            geometry_msgs::Point p;
            p.x = newx;
            p.y = newy;
            p.z = 0.0;
            path_marker.points.push_back(p);
        }
        fflush(fSol);

//
        obs_marker.points.clear();
        boat_marker.points.clear();

        // print the map (robot's view of the world and current plan)
        int startindex = startx_c + starty_c * size_x;
        int goalindex = goalx_c + goaly_c * size_x;
        for (int y = 0; bPrintMap && y < size_y; y++) {
            for (int x = 0; x < size_x; x++) {
                int index = x + y * size_x;
                int cost = map[index];
                cost = environment_navxythetalat.GetMapCost(x, y);

                // check to see if it is on the path
                bool bOnthePath = false;
                for (int j = 1; j < (int)solution_stateIDs_V.size(); j++) {
                    int newx, newy, newtheta = 0;
                    environment_navxythetalat.GetCoordFromState(solution_stateIDs_V[j], newx, newy, newtheta);
                    if (x == newx && y == newy) bOnthePath = true;
                }

                geometry_msgs::Point p;
                p.x = x + 0.5;
                p.y = y + 0.5;
                p.z = 0.0;

                if (index != startindex && index != goalindex && !bOnthePath) {
                    printf("%3d ", cost);

                    if (cost > 0) {
                        obs_marker.points.push_back(p);
                    }
                }
                else if (index == startindex) {
                    printf("  X ");
                    boat_marker.points.push_back(p);
                }
                else if (bOnthePath) {
                    printf("  * ");
                }
                else if (index == goalindex) {                  
                    printf("  G ");
                }
                else {
                    printf("? ");
                }
            }
            printf("\n");
        }


        marker_pub.publish(path_marker);
        marker_pub.publish(boat_marker);
        marker_pub.publish(obs_marker);









        // move along the path
        if (bPlanExists && (int)xythetaPath.size() > 1) {
            //get coord of the successor
            int newx, newy, newtheta;

            // move until we move into the end of motion primitive
            environment_navxythetalat.GetCoordFromState(solution_stateIDs_V[1], newx, newy, newtheta);

            printf("moving from %d %d %d to %d %d %d\n", startx_c, starty_c, starttheta_c, newx, newy, newtheta);

            // this check is weak since true configuration does not know the actual perimeter of the robot
            if (!trueenvironment_navxythetalat.IsValidConfiguration(newx, newy, newtheta)) {
                printf("ERROR: robot is commanded to move into an invalid configuration "
                       "according to true environment\n");
                throw new SBPL_Exception();
            }

            // move
            startx = DISCXY2CONT(newx, cellsize_m);
            starty = DISCXY2CONT(newy, cellsize_m);
            starttheta = DiscTheta2Cont(newtheta, num_thetas);

            // update the environment
            int newstartstateID = environment_navxythetalat.SetStart(startx, starty, starttheta);

            // update the planner
            if (planner->set_start(newstartstateID) == 0) {
                printf("ERROR: failed to update robot pose in the planner\n");
                throw new SBPL_Exception();
            }
        }
        else {
            printf("No move is made\n");
        }

        if (bPrint) {
            //printf("System Pause (return=%d)\n", system("pause"));
            cin >> dummy;
        }
    }

    printf("goal reached!\n");

    fflush(NULL);
    fclose(fSol);

    delete map;
    delete planner;

    return 1;
}

int main(int argc, char *argv[])
{
    planandnavigatexythetalat(PLANNER_TYPE_ARASTAR, argv[1], argv[2], 0, argc, argv);
}