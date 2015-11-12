/**********
 * angle.h - simple angle related functions
 * Jeff McMahill (jmcm@ri.cmu.edu)
 * National Robotics Engineering Consortium, Carnegie Mellon University
 * Copyright (c) 2008 Carnegie Mellon University and Jeffrey D. McMahill
 * All rights reserved.
 **********/

#ifndef DEG2RAD
#define DEG2RAD(d) ((d)*M_PI/180.0)
#endif

#ifndef RAD2DEG
#define RAD2DEG(r) ((r)*180.0/M_PI)
#endif

#ifdef __cplusplus
extern "C" {
#endif

double angle_norm_deg(double a);
double angle_norm_rad(double a);
double angle_diff_rad(double a, double b);
double angle_diff_deg(double a, double b);

#ifdef __cplusplus
}
#endif
