;; Auto-generated. Do not edit!


(when (boundp 'vcu_relay::vcu_cmd_drive)
  (if (not (find-package "VCU_RELAY"))
    (make-package "VCU_RELAY"))
  (shadow 'vcu_cmd_drive (find-package "VCU_RELAY")))
(unless (find-package "VCU_RELAY::VCU_CMD_DRIVE")
  (make-package "VCU_RELAY::VCU_CMD_DRIVE"))

(in-package "ROS")
;;//! \htmlinclude vcu_cmd_drive.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass vcu_relay::vcu_cmd_drive
  :super ros::object
  :slots (_header _port _stbd _steer ))

(defmethod vcu_relay::vcu_cmd_drive
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:port __port) 0.0)
    ((:stbd __stbd) 0.0)
    ((:steer __steer) 0.0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _port (float __port))
   (setq _stbd (float __stbd))
   (setq _steer (float __steer))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:port
   (&optional __port)
   (if __port (setq _port __port)) _port)
  (:stbd
   (&optional __stbd)
   (if __stbd (setq _stbd __stbd)) _stbd)
  (:steer
   (&optional __steer)
   (if __steer (setq _steer __steer)) _steer)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float32 _port
    4
    ;; float32 _stbd
    4
    ;; float32 _steer
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float32 _port
       (sys::poke _port (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _stbd
       (sys::poke _stbd (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _steer
       (sys::poke _steer (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float32 _port
     (setq _port (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _stbd
     (setq _stbd (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _steer
     (setq _steer (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get vcu_relay::vcu_cmd_drive :md5sum-) "571248e59ce03d7b264828ab2e3411c3")
(setf (get vcu_relay::vcu_cmd_drive :datatype-) "vcu_relay/vcu_cmd_drive")
(setf (get vcu_relay::vcu_cmd_drive :definition-)
      "Header header

float32 port
float32 stbd
float32 steer

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



(provide :vcu_relay/vcu_cmd_drive "571248e59ce03d7b264828ab2e3411c3")


