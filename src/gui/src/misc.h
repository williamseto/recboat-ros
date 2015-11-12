/**********
* misc.h - misc definitions for robot GUI
* Jeff McMahill (jmcm@frc.ri.cmu.edu)
* Field Robotics Center, Carnegie Mellon University
**********/

#ifndef M_PI
#define M_PI 3.14159265
#endif

struct float_box {
  int valid;
  float xstart, ystart;
  float xend, yend;
};

struct float_box3d {
  int valid;
  float xstart, ystart, zstart;
  float xend, yend, zend;
};

struct double_box {
  int valid;
  double xstart, ystart;
  double xend, yend;
};

struct double_box3d {
  int valid;
  double xstart, ystart, zstart;
  double xend, yend, zend;
};

struct double_rect {
  int valid;
  double x[4], y[4];
};

struct pose_type {
  double x, y, z;
  double roll, pitch, yaw;
};

#define MIN(a, b)	(((a) < (b)) ? (a) : (b))
#define MAX(a, b)	(((a) > (b)) ? (a) : (b))

#define D2R(x)	((x)/180.0*M_PI)
#define R2D(x)	((x)*180.0/M_PI)
//#define ABS(x)	((x) < 0 ? -(x) : (x))

#ifndef WIN32
#define Sleep(x) usleep(x*1000)
#endif
