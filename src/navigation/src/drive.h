/**********
 * drive.h - Driving controls
 * Jeff McMahill (jmcm@nrec.ri.cmu.edu)
 * National Robotics Engineering Center, Carnegie Mellon University
 * Copyright (c) 2015 Carnegie Mellon University
 * All rights reserved.
 **********/

#define DRIVE_RESET   (1<<0)   /* needs to be set on start or after pause */
#define DRIVE_END     (1<<1)   /* set for last segment, will slow down */

//#define DRIVE_LOOKAHEAD  40.0
#define DRIVE_LOOKAHEAD  30.0

#ifdef __cplusplus
extern "C" {
#endif

int drive_pure_pursuit_seg(int flags, float vel,
                           double sx, double sy, double gx, double gy,
                           double cx, double cy, double cyaw,
                           double *la_x, double *la_y, float *throttle, float *steer);
int drive_servo_yaw(int flags, float vel,
                    double target_yaw,
                    double cx, double cy, double cyaw,
                    float *throttle, float *steer);

#ifdef __cplusplus
}
#endif
