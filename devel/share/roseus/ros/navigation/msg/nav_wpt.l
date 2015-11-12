;; Auto-generated. Do not edit!


(when (boundp 'navigation::nav_wpt)
  (if (not (find-package "NAVIGATION"))
    (make-package "NAVIGATION"))
  (shadow 'nav_wpt (find-package "NAVIGATION")))
(unless (find-package "NAVIGATION::NAV_WPT")
  (make-package "NAVIGATION::NAV_WPT"))

(in-package "ROS")
;;//! \htmlinclude nav_wpt.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass navigation::nav_wpt
  :super ros::object
  :slots (_header _north _east _vel _action ))

(defmethod navigation::nav_wpt
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:north __north) 0.0)
    ((:east __east) 0.0)
    ((:vel __vel) 0.0)
    ((:action __action) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _north (float __north))
   (setq _east (float __east))
   (setq _vel (float __vel))
   (setq _action (round __action))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:north
   (&optional __north)
   (if __north (setq _north __north)) _north)
  (:east
   (&optional __east)
   (if __east (setq _east __east)) _east)
  (:vel
   (&optional __vel)
   (if __vel (setq _vel __vel)) _vel)
  (:action
   (&optional __action)
   (if __action (setq _action __action)) _action)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float64 _north
    8
    ;; float64 _east
    8
    ;; float32 _vel
    4
    ;; uint32 _action
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float64 _north
       (sys::poke _north (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _east
       (sys::poke _east (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float32 _vel
       (sys::poke _vel (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint32 _action
       (write-long _action s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float64 _north
     (setq _north (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _east
     (setq _east (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float32 _vel
     (setq _vel (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint32 _action
     (setq _action (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get navigation::nav_wpt :md5sum-) "09baa8a35c67a0a28096eac554dd6379")
(setf (get navigation::nav_wpt :datatype-) "navigation/nav_wpt")
(setf (get navigation::nav_wpt :definition-)
      "Header header
float64 north
float64 east

float32 vel

uint32 action

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



(provide :navigation/nav_wpt "09baa8a35c67a0a28096eac554dd6379")


