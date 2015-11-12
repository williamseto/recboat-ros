; Auto-generated. Do not edit!


(cl:in-package vcu_relay-msg)


;//! \htmlinclude vcu_cmd_drive.msg.html

(cl:defclass <vcu_cmd_drive> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (port
    :reader port
    :initarg :port
    :type cl:float
    :initform 0.0)
   (stbd
    :reader stbd
    :initarg :stbd
    :type cl:float
    :initform 0.0)
   (steer
    :reader steer
    :initarg :steer
    :type cl:float
    :initform 0.0))
)

(cl:defclass vcu_cmd_drive (<vcu_cmd_drive>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <vcu_cmd_drive>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'vcu_cmd_drive)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vcu_relay-msg:<vcu_cmd_drive> is deprecated: use vcu_relay-msg:vcu_cmd_drive instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <vcu_cmd_drive>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:header-val is deprecated.  Use vcu_relay-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'port-val :lambda-list '(m))
(cl:defmethod port-val ((m <vcu_cmd_drive>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:port-val is deprecated.  Use vcu_relay-msg:port instead.")
  (port m))

(cl:ensure-generic-function 'stbd-val :lambda-list '(m))
(cl:defmethod stbd-val ((m <vcu_cmd_drive>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:stbd-val is deprecated.  Use vcu_relay-msg:stbd instead.")
  (stbd m))

(cl:ensure-generic-function 'steer-val :lambda-list '(m))
(cl:defmethod steer-val ((m <vcu_cmd_drive>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:steer-val is deprecated.  Use vcu_relay-msg:steer instead.")
  (steer m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <vcu_cmd_drive>) ostream)
  "Serializes a message object of type '<vcu_cmd_drive>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'port))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'stbd))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'steer))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <vcu_cmd_drive>) istream)
  "Deserializes a message object of type '<vcu_cmd_drive>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'port) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'stbd) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'steer) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<vcu_cmd_drive>)))
  "Returns string type for a message object of type '<vcu_cmd_drive>"
  "vcu_relay/vcu_cmd_drive")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'vcu_cmd_drive)))
  "Returns string type for a message object of type 'vcu_cmd_drive"
  "vcu_relay/vcu_cmd_drive")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<vcu_cmd_drive>)))
  "Returns md5sum for a message object of type '<vcu_cmd_drive>"
  "571248e59ce03d7b264828ab2e3411c3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'vcu_cmd_drive)))
  "Returns md5sum for a message object of type 'vcu_cmd_drive"
  "571248e59ce03d7b264828ab2e3411c3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<vcu_cmd_drive>)))
  "Returns full string definition for message of type '<vcu_cmd_drive>"
  (cl:format cl:nil "Header header~%~%float32 port~%float32 stbd~%float32 steer~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'vcu_cmd_drive)))
  "Returns full string definition for message of type 'vcu_cmd_drive"
  (cl:format cl:nil "Header header~%~%float32 port~%float32 stbd~%float32 steer~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <vcu_cmd_drive>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <vcu_cmd_drive>))
  "Converts a ROS message object to a list"
  (cl:list 'vcu_cmd_drive
    (cl:cons ':header (header msg))
    (cl:cons ':port (port msg))
    (cl:cons ':stbd (stbd msg))
    (cl:cons ':steer (steer msg))
))
