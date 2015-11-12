/**********
 * recboat_interface.h - Recboat VCU interface
 * Jeff McMahill (jmcm@nrec.ri.cmu.edu)
 * National Robotics Engineering Center, Carnegie Mellon University
 * Copyright (c) 2015 Carnegie Mellon University and Jeffrey D. McMahill
 * All rights reserved.
 **********/

#ifdef WIN32
typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
#endif

/* commands to vehicle */
#define CMD_HEART      0  /* heartbeat */
#define CMD_STOP       2  /* stop */
#define CMD_LLCTRL    10  /* low level control */
#define CMD_TAKECTRL  11  /* take control from manual levers */
#define CMD_DRIVE     20

#define MSG_STATUS  100 /* status from vehicle */

/* VCU states */
#define STATE_STANDBY      0
#define STATE_AUTO         1
#define STATE_ESTOP        2

/* steering states */
#define STEER_OFF     0
#define STEER_HOLD    1
#define STEER_ACTIVE  2

struct recboat_status {
  uint32_t ver;   /* 0 */
  uint32_t sec;
  uint32_t usec;

  uint32_t state;  /* defined above */

  /* throttle / shift positions read back */
  float port_throttle;
  float stbd_throttle;
  float port_shift;
  float stbd_shift;

  /* commanded throttle positions */
  float port_throttle_out;
  float stbd_throttle_out;

  /* steering angle input */
  float steer_angle;

  /* inputs */
  uint8_t hci_switch;
  uint8_t port_ind;
  uint8_t stbd_ind;

  /* outputs */
  uint8_t remote_select;
  uint8_t autoled;

  uint8_t have_ctrl;   /* set if we have taken control of the throttle */

  float steer_angle_req;   /* requested steering angle */
  int steer_mode;          /* off, hold, or active */

  /* roboteq */
  int16_t rt_amps;   /* motor amps */
  int16_t rt_bamps;   /* battery amps */
  uint8_t rt_ff;      /* fault flag */
  uint8_t rt_fm;      /* runtime status */
  uint8_t rt_fs;      /* status flag */
  int16_t rt_power;   /* applied power */
  uint16_t rt_temp;   /* heatsink temperature */
  uint16_t rt_volt;   /* input voltage */
  
};
