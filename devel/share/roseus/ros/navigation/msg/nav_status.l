;; Auto-generated. Do not edit!


(when (boundp 'navigation::nav_status)
  (if (not (find-package "NAVIGATION"))
    (make-package "NAVIGATION"))
  (shadow 'nav_status (find-package "NAVIGATION")))
(unless (find-package "NAVIGATION::NAV_STATUS")
  (make-package "NAVIGATION::NAV_STATUS"))

(in-package "ROS")
;;//! \htmlinclude nav_status.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass navigation::nav_status
  :super ros::object
  :slots (_header _start_north _start_east _goal_north _goal_east _la_north _la_east _state ))

(defmethod navigation::nav_status
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:start_north __start_north) 0.0)
    ((:start_east __start_east) 0.0)
    ((:goal_north __goal_north) 0.0)
    ((:goal_east __goal_east) 0.0)
    ((:la_north __la_north) 0.0)
    ((:la_east __la_east) 0.0)
    ((:state __state) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _start_north (float __start_north))
   (setq _start_east (float __start_east))
   (setq _goal_north (float __goal_north))
   (setq _goal_east (float __goal_east))
   (setq _la_north (float __la_north))
   (setq _la_east (float __la_east))
   (setq _state (round __state))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:start_north
   (&optional __start_north)
   (if __start_north (setq _start_north __start_north)) _start_north)
  (:start_east
   (&optional __start_east)
   (if __start_east (setq _start_east __start_east)) _start_east)
  (:goal_north
   (&optional __goal_north)
   (if __goal_north (setq _goal_north __goal_north)) _goal_north)
  (:goal_east
   (&optional __goal_east)
   (if __goal_east (setq _goal_east __goal_east)) _goal_east)
  (:la_north
   (&optional __la_north)
   (if __la_north (setq _la_north __la_north)) _la_north)
  (:la_east
   (&optional __la_east)
   (if __la_east (setq _la_east __la_east)) _la_east)
  (:state
   (&optional __state)
   (if __state (setq _state __state)) _state)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float64 _start_north
    8
    ;; float64 _start_east
    8
    ;; float64 _goal_north
    8
    ;; float64 _goal_east
    8
    ;; float64 _la_north
    8
    ;; float64 _la_east
    8
    ;; uint32 _state
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float64 _start_north
       (sys::poke _start_north (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _start_east
       (sys::poke _start_east (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _goal_north
       (sys::poke _goal_north (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _goal_east
       (sys::poke _goal_east (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _la_north
       (sys::poke _la_north (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _la_east
       (sys::poke _la_east (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; uint32 _state
       (write-long _state s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float64 _start_north
     (setq _start_north (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _start_east
     (setq _start_east (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _goal_north
     (setq _goal_north (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _goal_east
     (setq _goal_east (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _la_north
     (setq _la_north (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _la_east
     (setq _la_east (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; uint32 _state
     (setq _state (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get navigation::nav_status :md5sum-) "d88d3bb1fcfc3d13a0bfef92f5caa348")
(setf (get navigation::nav_status :datatype-) "navigation/nav_status")
(setf (get navigation::nav_status :definition-)
      "Header header

float64 start_north
float64 start_east

float64 goal_north
float64 goal_east

float64 la_north
float64 la_east

uint32 state


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



(provide :navigation/nav_status "d88d3bb1fcfc3d13a0bfef92f5caa348")


