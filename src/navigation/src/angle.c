/*****
 * angle.c - simple angle functions
 * Jeff McMahill (jmcm@ri.cmu.edu)
 * National Robotics Engineering Consortium, Carnegie Mellon University
 * Copyright (c) 2008 Carnegie Mellon University and Jeffrey D. McMahill
 * All rights reserved.
 *****/

#include <stdio.h>
#include <sys/types.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265
#endif

#include "angle.h"

/* normalize an angle to -180 to 180 */
double angle_norm_deg(double a)
{

  while (a < -180.0) a += 360.0;
  while (a > 180.0) a -= 360.0;

  return(a);
}

/* normalize an angle to -PI to PI */
double angle_norm_rad(double a)
{

  while (a < -M_PI) a += M_PI*2.0;
  while (a > M_PI) a -= M_PI*2.0;

  return(a);
}

/* return a-b in the range -PI to PI */
double angle_diff_rad(double a, double b)
{

  return(angle_norm_rad(a-b));
}

/* return a-b in the range -180 to 180 */
double angle_diff_deg(double a, double b)
{

  return(angle_norm_deg(a-b));
}
