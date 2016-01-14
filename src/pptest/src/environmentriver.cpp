 #include "environmentriver.h"
 
 void EnvironmentRiver :: initializeEnv(char* envCfgFilename, char* motPrimFilename) 
   {
        // set the perimeter of the robot
        // it is given with 0, 0, 0 robot ref. point for which planning is done.
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

       if (!m_env.InitializeEnv(envCfgFilename, perimeterptsV, motPrimFilename))
       {
            printf("ERROR: InitializeEnv failed\n");
            throw SBPL_Exception();
       }
    }