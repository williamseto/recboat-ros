;; Auto-generated. Do not edit!


(when (boundp 'span_pose::span_pose)
  (if (not (find-package "SPAN_POSE"))
    (make-package "SPAN_POSE"))
  (shadow 'span_pose (find-package "SPAN_POSE")))
(unless (find-package "SPAN_POSE::SPAN_POSE")
  (make-package "SPAN_POSE::SPAN_POSE"))

(in-package "ROS")
;;//! \htmlinclude span_pose.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass span_pose::span_pose
  :super ros::object
  :slots (_header _ver _sec _usec _lat _lon _north _east _z _roll _pitch _yaw _vel _nsat _ins_stat _sol _pos _ins_str _sol_str _pos_str ))

(defmethod span_pose::span_pose
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:ver __ver) 0)
    ((:sec __sec) 0)
    ((:usec __usec) 0)
    ((:lat __lat) 0.0)
    ((:lon __lon) 0.0)
    ((:north __north) 0.0)
    ((:east __east) 0.0)
    ((:z __z) 0.0)
    ((:roll __roll) 0.0)
    ((:pitch __pitch) 0.0)
    ((:yaw __yaw) 0.0)
    ((:vel __vel) 0.0)
    ((:nsat __nsat) 0)
    ((:ins_stat __ins_stat) 0)
    ((:sol __sol) 0)
    ((:pos __pos) 0)
    ((:ins_str __ins_str) "")
    ((:sol_str __sol_str) "")
    ((:pos_str __pos_str) "")
    )
   (send-super :init)
   (setq _header __header)
   (setq _ver (round __ver))
   (setq _sec (round __sec))
   (setq _usec (round __usec))
   (setq _lat (float __lat))
   (setq _lon (float __lon))
   (setq _north (float __north))
   (setq _east (float __east))
   (setq _z (float __z))
   (setq _roll (float __roll))
   (setq _pitch (float __pitch))
   (setq _yaw (float __yaw))
   (setq _vel (float __vel))
   (setq _nsat (round __nsat))
   (setq _ins_stat (round __ins_stat))
   (setq _sol (round __sol))
   (setq _pos (round __pos))
   (setq _ins_str (string __ins_str))
   (setq _sol_str (string __sol_str))
   (setq _pos_str (string __pos_str))
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
  (:lat
   (&optional __lat)
   (if __lat (setq _lat __lat)) _lat)
  (:lon
   (&optional __lon)
   (if __lon (setq _lon __lon)) _lon)
  (:north
   (&optional __north)
   (if __north (setq _north __north)) _north)
  (:east
   (&optional __east)
   (if __east (setq _east __east)) _east)
  (:z
   (&optional __z)
   (if __z (setq _z __z)) _z)
  (:roll
   (&optional __roll)
   (if __roll (setq _roll __roll)) _roll)
  (:pitch
   (&optional __pitch)
   (if __pitch (setq _pitch __pitch)) _pitch)
  (:yaw
   (&optional __yaw)
   (if __yaw (setq _yaw __yaw)) _yaw)
  (:vel
   (&optional __vel)
   (if __vel (setq _vel __vel)) _vel)
  (:nsat
   (&optional __nsat)
   (if __nsat (setq _nsat __nsat)) _nsat)
  (:ins_stat
   (&optional __ins_stat)
   (if __ins_stat (setq _ins_stat __ins_stat)) _ins_stat)
  (:sol
   (&optional __sol)
   (if __sol (setq _sol __sol)) _sol)
  (:pos
   (&optional __pos)
   (if __pos (setq _pos __pos)) _pos)
  (:ins_str
   (&optional __ins_str)
   (if __ins_str (setq _ins_str __ins_str)) _ins_str)
  (:sol_str
   (&optional __sol_str)
   (if __sol_str (setq _sol_str __sol_str)) _sol_str)
  (:pos_str
   (&optional __pos_str)
   (if __pos_str (setq _pos_str __pos_str)) _pos_str)
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
    ;; float64 _lat
    8
    ;; float64 _lon
    8
    ;; float64 _north
    8
    ;; float64 _east
    8
    ;; float64 _z
    8
    ;; float32 _roll
    4
    ;; float32 _pitch
    4
    ;; float32 _yaw
    4
    ;; float32 _vel
    4
    ;; uint32 _nsat
    4
    ;; uint32 _ins_stat
    4
    ;; uint32 _sol
    4
    ;; uint32 _pos
    4
    ;; string _ins_str
    4 (length _ins_str)
    ;; string _sol_str
    4 (length _sol_str)
    ;; string _pos_str
    4 (length _pos_str)
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
     ;; float64 _lat
       (sys::poke _lat (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _lon
       (sys::poke _lon (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _north
       (sys::poke _north (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _east
       (sys::poke _east (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _z
       (sys::poke _z (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float32 _roll
       (sys::poke _roll (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _pitch
       (sys::poke _pitch (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _yaw
       (sys::poke _yaw (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _vel
       (sys::poke _vel (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint32 _nsat
       (write-long _nsat s)
     ;; uint32 _ins_stat
       (write-long _ins_stat s)
     ;; uint32 _sol
       (write-long _sol s)
     ;; uint32 _pos
       (write-long _pos s)
     ;; string _ins_str
       (write-long (length _ins_str) s) (princ _ins_str s)
     ;; string _sol_str
       (write-long (length _sol_str) s) (princ _sol_str s)
     ;; string _pos_str
       (write-long (length _pos_str) s) (princ _pos_str s)
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
   ;; float64 _lat
     (setq _lat (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _lon
     (setq _lon (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _north
     (setq _north (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _east
     (setq _east (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _z
     (setq _z (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float32 _roll
     (setq _roll (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _pitch
     (setq _pitch (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _yaw
     (setq _yaw (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _vel
     (setq _vel (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint32 _nsat
     (setq _nsat (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _ins_stat
     (setq _ins_stat (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _sol
     (setq _sol (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _pos
     (setq _pos (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; string _ins_str
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _ins_str (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _sol_str
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _sol_str (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _pos_str
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _pos_str (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(setf (get span_pose::span_pose :md5sum-) "23ce8b6d28cd252c454bfbb763592305")
(setf (get span_pose::span_pose :datatype-) "span_pose/span_pose")
(setf (get span_pose::span_pose :definition-)
      "Header header
uint32 ver
uint32 sec
uint32 usec

float64 lat
float64 lon

float64 north
float64 east
float64 z

float32 roll
float32 pitch
float32 yaw

float32 vel

uint32 nsat
uint32 ins_stat
uint32 sol
uint32 pos
string ins_str
string sol_str
string pos_str

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



(provide :span_pose/span_pose "23ce8b6d28cd252c454bfbb763592305")


