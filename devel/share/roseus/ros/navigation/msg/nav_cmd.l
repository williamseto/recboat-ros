;; Auto-generated. Do not edit!


(when (boundp 'navigation::nav_cmd)
  (if (not (find-package "NAVIGATION"))
    (make-package "NAVIGATION"))
  (shadow 'nav_cmd (find-package "NAVIGATION")))
(unless (find-package "NAVIGATION::NAV_CMD")
  (make-package "NAVIGATION::NAV_CMD"))

(in-package "ROS")
;;//! \htmlinclude nav_cmd.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass navigation::nav_cmd
  :super ros::object
  :slots (_header _cmd ))

(defmethod navigation::nav_cmd
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:cmd __cmd) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _cmd (round __cmd))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:cmd
   (&optional __cmd)
   (if __cmd (setq _cmd __cmd)) _cmd)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; uint32 _cmd
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; uint32 _cmd
       (write-long _cmd s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; uint32 _cmd
     (setq _cmd (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get navigation::nav_cmd :md5sum-) "dbd37f63c51c3fbd2f3c1270501d40b7")
(setf (get navigation::nav_cmd :datatype-) "navigation/nav_cmd")
(setf (get navigation::nav_cmd :definition-)
      "Header header

uint32 cmd

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



(provide :navigation/nav_cmd "dbd37f63c51c3fbd2f3c1270501d40b7")


