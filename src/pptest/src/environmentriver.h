#ifndef ENVIRONMENTRIVER_H
#define ENVIRONMENTRIVER_H

#include <sbpl/headers.h>

class EnvironmentRiver
{  
  private:
  std::vector<sbpl_2Dpt_t> perimeterptsV;
  sbpl_2Dpt_t pt_m;  
  public:  
  EnvironmentNAVXYTHETALAT m_env;
  
  void initializeEnv(char*, char*);
};

#endif