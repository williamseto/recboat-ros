;; Auto-generated. Do not edit!


(when (boundp 'navigation::nav_yaw)
  (if (not (find-package "NAVIGATION"))
    (make-package "NAVIGATION"))
  (shadow 'nav_yaw (find-package "NAVIGATION")))
(unless (find-package "NAVIGATION::NAV_YAW")
  (make-package "NAVIGATION::NAV_YAW"))

(in-package "ROS")
;;//! \htmlinclude nav_yaw.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass navigation::nav_yaw
  :super ros::object
  :slots (_header _yaw _vel _action ))

(defmethod navigation::nav_yaw
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:yaw __yaw) 0.0)
    ((:vel __vel) 0.0)
    ((:action __action) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _yaw (float __yaw))
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
  (:yaw
   (&optional __yaw)
   (if __yaw (setq _yaw __yaw)) _yaw)
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
    ;; float32 _yaw
    4
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
     ;; float32 _yaw
       (sys::poke _yaw (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
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
   ;; float32 _yaw
     (setq _yaw (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _vel
     (setq _vel (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint32 _action
     (setq _action (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get navigation::nav_yaw :md5sum-) "335e425fcd3dfa1c1439310c7bb41472")
(setf (get navigation::nav_yaw :datatype-) "navigation/nav_yaw")
(setf (get navigation::nav_yaw :definition-)
      "Header header
float32 yaw
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



(provide :navigation/nav_yaw "335e425fcd3dfa1c1439310c7bb41472")


