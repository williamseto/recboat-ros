/**********
Interface to communicate with ROS and the waypoint follower
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

  
  unsigned int nsat;
  unsigned int ins_stat;
  unsigned int sol;
  unsigned int pos;
  char ins_str[30];
  char sol_str[30];
  char pos_str[30];
};


int ros_init(int *argc, char ***argv);
void ros_exit();
int ros_nav_cmd(int cmd);
int ros_nav_wpt(double north, double east, float vel, int action);
int ros_vcu_estop(int state);

extern struct ros_pose_status cur_pose_status;
void *ros_thread(void *d);



