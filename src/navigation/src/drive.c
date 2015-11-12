/**********
 * drive.c - Driving controls
 * Jeff McMahill (jmcm@nrec.ri.cmu.edu)
 * National Robotics Engineering Center, Carnegie Mellon University
 * Copyright (c) 2015 Carnegie Mellon University
 * All rights reserved.
 **********/

#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>

#include "angle.h"
#include "drive.h"

static double pt_distsqr(double x0, double y0, double x1, double y1)
{
  double d;

  d = (x1-x0)*(x1-x0) + (y1-y0)*(y1-y0);

  return(d);
}

static double pt_dist(double x0, double y0, double x1, double y1)
{
  double d;

  d = sqrt((x1-x0)*(x1-x0) + (y1-y0)*(y1-y0));

  return(d);
}

static double pt_line_dist(double x[3], double y[3], double *cpx, double *cpy)
{
  double u, d;

  d = pt_distsqr(x[0], y[0], x[1], y[1]);
  if (d < 0.000001) return(pt_dist(x[0], y[0], x[2], y[2]));

  u = ((x[2]-x[0])*(x[1]-x[0]) + (y[2]-y[0])*(y[1]-y[0])) / d;

  //  printf("u = %f  d = %f\n", u, d);

  *cpx = x[0] + u*(x[1]-x[0]);
  *cpy = y[0] + u*(y[1]-y[0]);

  d = pt_dist(*cpx, *cpy, x[2], y[2]);

  return(d);
}

static double pt_line_sdist(double x[3], double y[3], double *cpx, double *cpy)
{
  double u, d, s;

  d = pt_distsqr(x[0], y[0], x[1], y[1]);
  if (d < 0.000001) return(pt_dist(x[0], y[0], x[2], y[2]));

  u = ((x[2]-x[0])*(x[1]-x[0]) + (y[2]-y[0])*(y[1]-y[0])) / d;

  //  printf("u = %f  d = %f\n", u, d);

  *cpx = x[0] + u*(x[1]-x[0]);
  *cpy = y[0] + u*(y[1]-y[0]);

  d = pt_dist(*cpx, *cpy, x[2], y[2]);

  s = (x[1] - x[0]) * (y[2] - y[0]) - (y[1] - y[0]) * (x[2] - x[0]);
  if (s < 0.0) d = -d;

  return(d);
}

static int find_goal(double sx, double sy, double gx, double gy,
                     double cx, double cy, double *ox, double *oy)
{
  double u, d;
  int ret = 0;

  d = pt_distsqr(sx, sy, gx, gy);
  if (d < 0.001) {
    *ox = sx;
    *oy = sy;
    return(1);
  }

  u = ((cx-sx)*(gx-sx) + (cy-sy)*(gy-sy)) / d;
  if (u > 1.0) ret = 1;

  u += DRIVE_LOOKAHEAD / sqrt(d);

  //  printf("u = %f  d = %f\n", u, d);

  *ox = sx + u*(gx-sx);
  *oy = sy + u*(gy-sy);

  //  *ox = gx;
  //  *oy = gy;

  return(ret);
}

int drive_pure_pursuit_seg(int flags, float vel,
                           double sx, double sy, double gx, double gy,
                           double cx, double cy, double cyaw,
                           double *la_x, double *la_y, float *throttle, float *steer)
{
  double dist = 0.0, dx, dy;
  double threshold = 15.0, v = vel;
  float s = 0.0;

  //  double P = 1.0;
  //  double I = 0.0;
  //  double D = 2.0;

  double P = 1.6;
  double I = 0.0;
  double D = 5.0;

  double err = 0.0;
  static double err_old = 0.0, err_old2 = 0.0;
  static double cv = 0.0;
  double curyaw, yaw;
  double x, y;  /* current goal */
  int ret;

  if (flags & DRIVE_RESET) {
    err_old = 0.0;
    err_old2 = 0.0;
    cv = 0.0;
  }

  ret = find_goal(sx, sy, gx, gy, cx, cy, &x, &y);
  *la_x = x;
  *la_y = y;
  if (ret) {
    if (flags & DRIVE_END) {
      *throttle = 0.0;
      *steer = 0.0;
    } else {
      *throttle = vel;
      *steer = 0.0;
    }
    printf("end of segment!\n");
    return(0);  /* past end of segment */
  }

  dx = x - cx;
  dy = y - cy;
  //	 yaw = atan2(dy, dx) + M_PI;
  yaw = atan2(dy, dx);
  if (yaw < 0.0) yaw += 2.0*M_PI;
  if (vel < 0.0) {
    curyaw = cyaw + M_PI;
    curyaw = angle_norm_rad(curyaw);
  }
  else
    curyaw = cyaw;
  err = angle_diff_rad(curyaw, yaw);

  dist = pt_dist(cx, cy, gx, gy);

  if (dist < threshold) {
    if (flags & DRIVE_END) {
      *throttle = 0.0;
      *steer = 0.0;
    } else {
      *throttle = vel;
      *steer = 0.0;
    }
    printf("end of segment!\n");
    return(0);  /* past end of segment */
  }

  v = vel;

  if ((flags & DRIVE_END) && dist < threshold) v = vel/2.0;

  if (v > 0.0 && v < 0.1) v = 0.1;
  if (v < 0.0 && v > -0.1) v = -0.1;

  cv += P*(err - err_old) + I*err + D*(err - 2.0*err_old + err_old2);

  err_old2 = err_old;
  err_old = err;

  s = cv;

  printf("driving, v: %.2f yaw: %.2f cur: %.2f s: %f dist: %.2f err: %f\n", v, RAD2DEG(yaw), RAD2DEG(curyaw), s, dist, err);

  s /= 3.0;

  if (s > 1.0) s = 1.0;
  if (s < -1.0) s = -1.0;

  //  if (v > 0.5) v = 0.5;
  if (v > 1.0) v = 1.0;

  *throttle = v;
  *steer = -s;

  return(1);

}

int drive_servo_yaw(int flags, float vel,
                    double target_yaw,
                    double cx, double cy, double cyaw,
                    float *throttle, float *steer)
{
  double dist = 0.0, dx, dy;
  double threshold = 5.0, v = vel;
  float s = 0.0;

  //  double P = 1.0;
  //  double I = 0.0;
  //  double D = 2.0;

  double P = 1.6;
  double I = 0.0;
  double D = 5.0;

  double err = 0.0;
  static double err_old = 0.0, err_old2 = 0.0;
  static double cv = 0.0;
  double curyaw, yaw;
  double x, y;  /* current goal */
  int ret;

  if (flags & DRIVE_RESET) {
    err_old = 0.0;
    err_old2 = 0.0;
    cv = 0.0;
  }

  yaw = target_yaw;
  if (yaw < 0.0) yaw += 2.0*M_PI;

  if (vel < 0.0) {
    curyaw = cyaw + M_PI;
    curyaw = angle_norm_rad(curyaw);
  }
  else
    curyaw = cyaw;
  err = angle_diff_rad(curyaw, yaw);

  v = vel;

  cv += P*(err - err_old) + I*err + D*(err - 2.0*err_old + err_old2);

  err_old2 = err_old;
  err_old = err;

  s = cv;

  printf("driving, v: %.2f yaw: %.2f cur: %.2f s: %f err: %f\n", v, RAD2DEG(yaw), RAD2DEG(curyaw), s, err);

  s /= 3.0;

  if (s > 1.0) s = 1.0;
  if (s < -1.0) s = -1.0;

  //  if (v > 0.5) v = 0.5;
  if (v > 1.0) v = 1.0;

  *throttle = v;
  *steer = -s;

  return(1);

}
