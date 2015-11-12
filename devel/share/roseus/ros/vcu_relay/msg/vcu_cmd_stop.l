;; Auto-generated. Do not edit!


(when (boundp 'vcu_relay::vcu_cmd_stop)
  (if (not (find-package "VCU_RELAY"))
    (make-package "VCU_RELAY"))
  (shadow 'vcu_cmd_stop (find-package "VCU_RELAY")))
(unless (find-package "VCU_RELAY::VCU_CMD_STOP")
  (make-package "VCU_RELAY::VCU_CMD_STOP"))

(in-package "ROS")
;;//! \htmlinclude vcu_cmd_stop.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass vcu_relay::vcu_cmd_stop
  :super ros::object
  :slots (_header _stop ))

(defmethod vcu_relay::vcu_cmd_stop
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:stop __stop) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _stop (round __stop))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:stop
   (&optional __stop)
   (if __stop (setq _stop __stop)) _stop)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; uint8 _stop
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; uint8 _stop
       (write-byte _stop s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; uint8 _stop
     (setq _stop (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get vcu_relay::vcu_cmd_stop :md5sum-) "91ec01ff4a319869482b53466d6a3660")
(setf (get vcu_relay::vcu_cmd_stop :datatype-) "vcu_relay/vcu_cmd_stop")
(setf (get vcu_relay::vcu_cmd_stop :definition-)
      "Header header

uint8 stop

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



(provide :vcu_relay/vcu_cmd_stop "91ec01ff4a319869482b53466d6a3660")


