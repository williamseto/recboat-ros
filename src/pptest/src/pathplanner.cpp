#include "pathplanner.h"

PathPlanner :: PathPlanner()
{
         m_planner = NULL;
}

void PathPlanner :: initializePlanner(EnvironmentNAVXYTHETALAT* m_env)
{

        double initialEpsilon = 3.0;
        bool bsearchuntilfirstsolution = false;
        bool bforwardsearch = false;

        m_planner = new ARAPlanner(m_env, bforwardsearch);
     //get start and goal from env
        MDPConfig MDPCfg;

        // initialize MDP info
        if (!m_env->InitializeMDPCfg(&MDPCfg)) {
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


 int PathPlanner :: runPlannerOnce(EnvironmentNAVXYTHETALAT* m_env, BoatPosition boatPosition, BoatGoal boatGoal) 
 {
        //scale start & goal according to resolution of map
        //currently hard-coded to 5 meters per pixel
        double startx = boatPosition.m_boatX * 5.08;
        double starty = boatPosition.m_boatY * 5.08;

        double goalx = boatGoal.m_goalX * 5.08;
        double goaly = boatGoal.m_goalY * 5.08;

        //convert from heading to (x,y,theta) convention
        double starttheta = (boatPosition.m_boatYaw - M_PI/2) * -1;
        std::cout<<"\nstartx: "<<startx<<", starty: "<<starty<<", starttheta: "<<starttheta;
        //printf("%f %f %f\n", m_boatX, m_boatY, m_boatYaw);

        int newstartstateID = m_env->SetStart(startx, starty, starttheta);
        int newgoalstateID = m_env->SetGoal(goalx, goaly, boatGoal.m_goalTheta);


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
