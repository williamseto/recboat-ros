; Auto-generated. Do not edit!


(cl:in-package vcu_relay-msg)


;//! \htmlinclude vcu_cmd_stop.msg.html

(cl:defclass <vcu_cmd_stop> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (stop
    :reader stop
    :initarg :stop
    :type cl:fixnum
    :initform 0))
)

(cl:defclass vcu_cmd_stop (<vcu_cmd_stop>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <vcu_cmd_stop>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'vcu_cmd_stop)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vcu_relay-msg:<vcu_cmd_stop> is deprecated: use vcu_relay-msg:vcu_cmd_stop instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <vcu_cmd_stop>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:header-val is deprecated.  Use vcu_relay-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'stop-val :lambda-list '(m))
(cl:defmethod stop-val ((m <vcu_cmd_stop>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:stop-val is deprecated.  Use vcu_relay-msg:stop instead.")
  (stop m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <vcu_cmd_stop>) ostream)
  "Serializes a message object of type '<vcu_cmd_stop>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'stop)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <vcu_cmd_stop>) istream)
  "Deserializes a message object of type '<vcu_cmd_stop>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'stop)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<vcu_cmd_stop>)))
  "Returns string type for a message object of type '<vcu_cmd_stop>"
  "vcu_relay/vcu_cmd_stop")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'vcu_cmd_stop)))
  "Returns string type for a message object of type 'vcu_cmd_stop"
  "vcu_relay/vcu_cmd_stop")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<vcu_cmd_stop>)))
  "Returns md5sum for a message object of type '<vcu_cmd_stop>"
  "91ec01ff4a319869482b53466d6a3660")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'vcu_cmd_stop)))
  "Returns md5sum for a message object of type 'vcu_cmd_stop"
  "91ec01ff4a319869482b53466d6a3660")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<vcu_cmd_stop>)))
  "Returns full string definition for message of type '<vcu_cmd_stop>"
  (cl:format cl:nil "Header header~%~%uint8 stop~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'vcu_cmd_stop)))
  "Returns full string definition for message of type 'vcu_cmd_stop"
  (cl:format cl:nil "Header header~%~%uint8 stop~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <vcu_cmd_stop>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <vcu_cmd_stop>))
  "Converts a ROS message object to a list"
  (cl:list 'vcu_cmd_stop
    (cl:cons ':header (header msg))
    (cl:cons ':stop (stop msg))
))
