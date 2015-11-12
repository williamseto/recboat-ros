Header header
uint32 ver
uint32 sec
uint32 usec

uint32 state

# throttle / shift positions read back
float32 port_throttle
float32 stbd_throttle
float32 port_shift
float32 stbd_shift

# commanded throttle positions
float32 port_throttle_out
float32 stbd_throttle_out

# steering angle input
float32 steer_angle

# inputs
uint8 hci_switch
uint8 port_ind
uint8 stbd_ind

# outputs
uint8 remote_select
uint8 autoled

uint8 have_ctrl

float32 steer_angle_req
int32 steer_mode

# roboteq status
int16 rt_amps   # motor amps
int16 rt_bamps  # battery amps
uint8 rt_ff     # fault flag
uint8 rt_fm     # runtime status
uint8 rt_fs     # status flag
int16 rt_power  # applied power
uint16 rt_temp  # heatsink temperature
uint16 rt_volt  # input voltage
