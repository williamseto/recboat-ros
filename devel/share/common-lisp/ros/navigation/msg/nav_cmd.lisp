; Auto-generated. Do not edit!


(cl:in-package navigation-msg)


;//! \htmlinclude nav_cmd.msg.html

(cl:defclass <nav_cmd> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (cmd
    :reader cmd
    :initarg :cmd
    :type cl:integer
    :initform 0))
)

(cl:defclass nav_cmd (<nav_cmd>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <nav_cmd>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'nav_cmd)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name navigation-msg:<nav_cmd> is deprecated: use navigation-msg:nav_cmd instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <nav_cmd>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader navigation-msg:header-val is deprecated.  Use navigation-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'cmd-val :lambda-list '(m))
(cl:defmethod cmd-val ((m <nav_cmd>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader navigation-msg:cmd-val is deprecated.  Use navigation-msg:cmd instead.")
  (cmd m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <nav_cmd>) ostream)
  "Serializes a message object of type '<nav_cmd>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'cmd)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'cmd)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'cmd)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'cmd)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <nav_cmd>) istream)
  "Deserializes a message object of type '<nav_cmd>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'cmd)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'cmd)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'cmd)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'cmd)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<nav_cmd>)))
  "Returns string type for a message object of type '<nav_cmd>"
  "navigation/nav_cmd")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'nav_cmd)))
  "Returns string type for a message object of type 'nav_cmd"
  "navigation/nav_cmd")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<nav_cmd>)))
  "Returns md5sum for a message object of type '<nav_cmd>"
  "dbd37f63c51c3fbd2f3c1270501d40b7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'nav_cmd)))
  "Returns md5sum for a message object of type 'nav_cmd"
  "dbd37f63c51c3fbd2f3c1270501d40b7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<nav_cmd>)))
  "Returns full string definition for message of type '<nav_cmd>"
  (cl:format cl:nil "Header header~%~%uint32 cmd~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'nav_cmd)))
  "Returns full string definition for message of type 'nav_cmd"
  (cl:format cl:nil "Header header~%~%uint32 cmd~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <nav_cmd>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <nav_cmd>))
  "Converts a ROS message object to a list"
  (cl:list 'nav_cmd
    (cl:cons ':header (header msg))
    (cl:cons ':cmd (cmd msg))
))
