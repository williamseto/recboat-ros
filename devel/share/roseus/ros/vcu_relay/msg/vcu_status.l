;; Auto-generated. Do not edit!


(when (boundp 'vcu_relay::vcu_status)
  (if (not (find-package "VCU_RELAY"))
    (make-package "VCU_RELAY"))
  (shadow 'vcu_status (find-package "VCU_RELAY")))
(unless (find-package "VCU_RELAY::VCU_STATUS")
  (make-package "VCU_RELAY::VCU_STATUS"))

(in-package "ROS")
;;//! \htmlinclude vcu_status.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass vcu_relay::vcu_status
  :super ros::object
  :slots (_header _ver _sec _usec _state _port_throttle _stbd_throttle _port_shift _stbd_shift _port_throttle_out _stbd_throttle_out _steer_angle _hci_switch _port_ind _stbd_ind _remote_select _autoled _have_ctrl _steer_angle_req _steer_mode _rt_amps _rt_bamps _rt_ff _rt_fm _rt_fs _rt_power _rt_temp _rt_volt ))

(defmethod vcu_relay::vcu_status
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:ver __ver) 0)
    ((:sec __sec) 0)
    ((:usec __usec) 0)
    ((:state __state) 0)
    ((:port_throttle __port_throttle) 0.0)
    ((:stbd_throttle __stbd_throttle) 0.0)
    ((:port_shift __port_shift) 0.0)
    ((:stbd_shift __stbd_shift) 0.0)
    ((:port_throttle_out __port_throttle_out) 0.0)
    ((:stbd_throttle_out __stbd_throttle_out) 0.0)
    ((:steer_angle __steer_angle) 0.0)
    ((:hci_switch __hci_switch) 0)
    ((:port_ind __port_ind) 0)
    ((:stbd_ind __stbd_ind) 0)
    ((:remote_select __remote_select) 0)
    ((:autoled __autoled) 0)
    ((:have_ctrl __have_ctrl) 0)
    ((:steer_angle_req __steer_angle_req) 0.0)
    ((:steer_mode __steer_mode) 0)
    ((:rt_amps __rt_amps) 0)
    ((:rt_bamps __rt_bamps) 0)
    ((:rt_ff __rt_ff) 0)
    ((:rt_fm __rt_fm) 0)
    ((:rt_fs __rt_fs) 0)
    ((:rt_power __rt_power) 0)
    ((:rt_temp __rt_temp) 0)
    ((:rt_volt __rt_volt) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _ver (round __ver))
   (setq _sec (round __sec))
   (setq _usec (round __usec))
   (setq _state (round __state))
   (setq _port_throttle (float __port_throttle))
   (setq _stbd_throttle (float __stbd_throttle))
   (setq _port_shift (float __port_shift))
   (setq _stbd_shift (float __stbd_shift))
   (setq _port_throttle_out (float __port_throttle_out))
   (setq _stbd_throttle_out (float __stbd_throttle_out))
   (setq _steer_angle (float __steer_angle))
   (setq _hci_switch (round __hci_switch))
   (setq _port_ind (round __port_ind))
   (setq _stbd_ind (round __stbd_ind))
   (setq _remote_select (round __remote_select))
   (setq _autoled (round __autoled))
   (setq _have_ctrl (round __have_ctrl))
   (setq _steer_angle_req (float __steer_angle_req))
   (setq _steer_mode (round __steer_mode))
   (setq _rt_amps (round __rt_amps))
   (setq _rt_bamps (round __rt_bamps))
   (setq _rt_ff (round __rt_ff))
   (setq _rt_fm (round __rt_fm))
   (setq _rt_fs (round __rt_fs))
   (setq _rt_power (round __rt_power))
   (setq _rt_temp (round __rt_temp))
   (setq _rt_volt (round __rt_volt))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:ver
   (&optional __ver)
   (if __ver (setq _ver __ver)) _ver)
  (:sec
   (&optional __sec)
   (if __sec (setq _sec __sec)) _sec)
  (:usec
   (&optional __usec)
   (if __usec (setq _usec __usec)) _usec)
  (:state
   (&optional __state)
   (if __state (setq _state __state)) _state)
  (:port_throttle
   (&optional __port_throttle)
   (if __port_throttle (setq _port_throttle __port_throttle)) _port_throttle)
  (:stbd_throttle
   (&optional __stbd_throttle)
   (if __stbd_throttle (setq _stbd_throttle __stbd_throttle)) _stbd_throttle)
  (:port_shift
   (&optional __port_shift)
   (if __port_shift (setq _port_shift __port_shift)) _port_shift)
  (:stbd_shift
   (&optional __stbd_shift)
   (if __stbd_shift (setq _stbd_shift __stbd_shift)) _stbd_shift)
  (:port_throttle_out
   (&optional __port_throttle_out)
   (if __port_throttle_out (setq _port_throttle_out __port_throttle_out)) _port_throttle_out)
  (:stbd_throttle_out
   (&optional __stbd_throttle_out)
   (if __stbd_throttle_out (setq _stbd_throttle_out __stbd_throttle_out)) _stbd_throttle_out)
  (:steer_angle
   (&optional __steer_angle)
   (if __steer_angle (setq _steer_angle __steer_angle)) _steer_angle)
  (:hci_switch
   (&optional __hci_switch)
   (if __hci_switch (setq _hci_switch __hci_switch)) _hci_switch)
  (:port_ind
   (&optional __port_ind)
   (if __port_ind (setq _port_ind __port_ind)) _port_ind)
  (:stbd_ind
   (&optional __stbd_ind)
   (if __stbd_ind (setq _stbd_ind __stbd_ind)) _stbd_ind)
  (:remote_select
   (&optional __remote_select)
   (if __remote_select (setq _remote_select __remote_select)) _remote_select)
  (:autoled
   (&optional __autoled)
   (if __autoled (setq _autoled __autoled)) _autoled)
  (:have_ctrl
   (&optional __have_ctrl)
   (if __have_ctrl (setq _have_ctrl __have_ctrl)) _have_ctrl)
  (:steer_angle_req
   (&optional __steer_angle_req)
   (if __steer_angle_req (setq _steer_angle_req __steer_angle_req)) _steer_angle_req)
  (:steer_mode
   (&optional __steer_mode)
   (if __steer_mode (setq _steer_mode __steer_mode)) _steer_mode)
  (:rt_amps
   (&optional __rt_amps)
   (if __rt_amps (setq _rt_amps __rt_amps)) _rt_amps)
  (:rt_bamps
   (&optional __rt_bamps)
   (if __rt_bamps (setq _rt_bamps __rt_bamps)) _rt_bamps)
  (:rt_ff
   (&optional __rt_ff)
   (if __rt_ff (setq _rt_ff __rt_ff)) _rt_ff)
  (:rt_fm
   (&optional __rt_fm)
   (if __rt_fm (setq _rt_fm __rt_fm)) _rt_fm)
  (:rt_fs
   (&optional __rt_fs)
   (if __rt_fs (setq _rt_fs __rt_fs)) _rt_fs)
  (:rt_power
   (&optional __rt_power)
   (if __rt_power (setq _rt_power __rt_power)) _rt_power)
  (:rt_temp
   (&optional __rt_temp)
   (if __rt_temp (setq _rt_temp __rt_temp)) _rt_temp)
  (:rt_volt
   (&optional __rt_volt)
   (if __rt_volt (setq _rt_volt __rt_volt)) _rt_volt)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; uint32 _ver
    4
    ;; uint32 _sec
    4
    ;; uint32 _usec
    4
    ;; uint32 _state
    4
    ;; float32 _port_throttle
    4
    ;; float32 _stbd_throttle
    4
    ;; float32 _port_shift
    4
    ;; float32 _stbd_shift
    4
    ;; float32 _port_throttle_out
    4
    ;; float32 _stbd_throttle_out
    4
    ;; float32 _steer_angle
    4
    ;; uint8 _hci_switch
    1
    ;; uint8 _port_ind
    1
    ;; uint8 _stbd_ind
    1
    ;; uint8 _remote_select
    1
    ;; uint8 _autoled
    1
    ;; uint8 _have_ctrl
    1
    ;; float32 _steer_angle_req
    4
    ;; int32 _steer_mode
    4
    ;; int16 _rt_amps
    2
    ;; int16 _rt_bamps
    2
    ;; uint8 _rt_ff
    1
    ;; uint8 _rt_fm
    1
    ;; uint8 _rt_fs
    1
    ;; int16 _rt_power
    2
    ;; uint16 _rt_temp
    2
    ;; uint16 _rt_volt
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; uint32 _ver
       (write-long _ver s)
     ;; uint32 _sec
       (write-long _sec s)
     ;; uint32 _usec
       (write-long _usec s)
     ;; uint32 _state
       (write-long _state s)
     ;; float32 _port_throttle
       (sys::poke _port_throttle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _stbd_throttle
       (sys::poke _stbd_throttle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _port_shift
       (sys::poke _port_shift (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _stbd_shift
       (sys::poke _stbd_shift (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _port_throttle_out
       (sys::poke _port_throttle_out (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _stbd_throttle_out
       (sys::poke _stbd_throttle_out (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _steer_angle
       (sys::poke _steer_angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint8 _hci_switch
       (write-byte _hci_switch s)
     ;; uint8 _port_ind
       (write-byte _port_ind s)
     ;; uint8 _stbd_ind
       (write-byte _stbd_ind s)
     ;; uint8 _remote_select
       (write-byte _remote_select s)
     ;; uint8 _autoled
       (write-byte _autoled s)
     ;; uint8 _have_ctrl
       (write-byte _have_ctrl s)
     ;; float32 _steer_angle_req
       (sys::poke _steer_angle_req (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; int32 _steer_mode
       (write-long _steer_mode s)
     ;; int16 _rt_amps
       (write-word _rt_amps s)
     ;; int16 _rt_bamps
       (write-word _rt_bamps s)
     ;; uint8 _rt_ff
       (write-byte _rt_ff s)
     ;; uint8 _rt_fm
       (write-byte _rt_fm s)
     ;; uint8 _rt_fs
       (write-byte _rt_fs s)
     ;; int16 _rt_power
       (write-word _rt_power s)
     ;; uint16 _rt_temp
       (write-word _rt_temp s)
     ;; uint16 _rt_volt
       (write-word _rt_volt s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; uint32 _ver
     (setq _ver (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _sec
     (setq _sec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _usec
     (setq _usec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _state
     (setq _state (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float32 _port_throttle
     (setq _port_throttle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _stbd_throttle
     (setq _stbd_throttle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _port_shift
     (setq _port_shift (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _stbd_shift
     (setq _stbd_shift (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _port_throttle_out
     (setq _port_throttle_out (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _stbd_throttle_out
     (setq _stbd_throttle_out (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _steer_angle
     (setq _steer_angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint8 _hci_switch
     (setq _hci_switch (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _port_ind
     (setq _port_ind (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _stbd_ind
     (setq _stbd_ind (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _remote_select
     (setq _remote_select (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _autoled
     (setq _autoled (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _have_ctrl
     (setq _have_ctrl (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float32 _steer_angle_req
     (setq _steer_angle_req (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; int32 _steer_mode
     (setq _steer_mode (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int16 _rt_amps
     (setq _rt_amps (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _rt_bamps
     (setq _rt_bamps (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint8 _rt_ff
     (setq _rt_ff (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _rt_fm
     (setq _rt_fm (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _rt_fs
     (setq _rt_fs (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; int16 _rt_power
     (setq _rt_power (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _rt_temp
     (setq _rt_temp (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _rt_volt
     (setq _rt_volt (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get vcu_relay::vcu_status :md5sum-) "b5c6dfd3e6cfa86f2afab134f3b7116c")
(setf (get vcu_relay::vcu_status :datatype-) "vcu_relay/vcu_status")
(setf (get vcu_relay::vcu_status :definition-)
      "Header header
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

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

")



(provide :vcu_relay/vcu_status "b5c6dfd3e6cfa86f2afab134f3b7116c")


