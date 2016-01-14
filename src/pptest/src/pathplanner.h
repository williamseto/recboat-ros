#ifndef PATHPLANNER_H
#define PATHPLANNER_H

#include "boatlocation.h"
#include <sbpl/headers.h>

class PathPlanner
{
    private:
    SBPLPlanner* m_planner;
        
    public:       
    std::vector<int> m_solutionIDs;
    
    PathPlanner();
    
    void initializePlanner(EnvironmentNAVXYTHETALAT* m_env);    
    int runPlannerOnce(EnvironmentNAVXYTHETALAT* m_env, BoatPosition boatPosition, BoatGoal boatGoal);
};

#endif