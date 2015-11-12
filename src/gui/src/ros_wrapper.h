/**********
 * ros_thread.cpp - Recboat gui ROS interface
 * Jeff McMahill (jmcm@nrec.ri.cmu.edu)
 * National Robotics Engineering Center, Carnegie Mellon University
 * Copyright (c) 2015 Carnegie Mellon University
 * All rights reserved.
 **********/

struct ros_pose_status {
  double lat;
  double lon;
  
  double north;
  double east;
  double alt;

  float roll;
  float pitch;
  float yaw;
  
  float vel;

  uint32_t nsat;
  uint32_t ins_stat;
  uint32_t sol;
  uint32_t pos;
  char ins_str[30];
  char sol_str[30];
  char pos_str[30];
};

/* VCU states */
#define VCU_STATE_STANDBY      0
#define VCU_STATE_AUTO         1
#define VCU_STATE_ESTOP        2

/* steering states */
#define STEER_OFF     0
#define STEER_HOLD    1
#define STEER_ACTIVE  2

struct ros_vcu_status {
  uint32_t state;

// throttle / shift positions read back
  float port_throttle;
  float stbd_throttle;
  float port_shift;
  float stbd_shift;

// commanded throttle positions
  float port_throttle_out;
  float stbd_throttle_out;

// steering angle input
  float steer_angle;

// inputs
  uint8_t hci_switch;
  uint8_t port_ind;
  uint8_t stbd_ind;

// outputs
  uint8_t remote_select;
  uint8_t autoled;

  uint8_t have_ctrl;

  float steer_angle_req;
  int32_t steer_mode;

// roboteq status
  int16_t rt_amps;   // motor amps
  int16_t rt_bamps;  // battery amps
  uint8_t rt_ff;     // fault flag
  uint8_t rt_fm;     // runtime status
  uint8_t rt_fs;     // status flag
  int16_t rt_power;  // applied power
  uint16_t rt_temp;  // heatsink temperature
  uint16_t rt_volt;  // input voltage

};

struct ros_nav_status {
  double start_north;
  double start_east;

  double goal_north;
  double goal_east;

  double la_north;
  double la_east;

  uint32_t state;
};

#ifdef __cplusplus
extern "C" {
#endif

void *ros_thread(void *d);
void ros_init(int *argc, char ***argv);
void ros_exit();

int ros_nav_cmd(int cmd);
int ros_nav_wpt(double north, double east, float vel, int action);
int ros_vcu_estop(int state);

extern struct ros_vcu_status cur_vcu_status;
extern struct ros_pose_status cur_pose_status;
extern struct ros_nav_status cur_nav_status;

#ifdef __cplusplus
}
#endif
