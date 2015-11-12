; Auto-generated. Do not edit!


(cl:in-package navigation-msg)


;//! \htmlinclude nav_wpt.msg.html

(cl:defclass <nav_wpt> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (north
    :reader north
    :initarg :north
    :type cl:float
    :initform 0.0)
   (east
    :reader east
    :initarg :east
    :type cl:float
    :initform 0.0)
   (vel
    :reader vel
    :initarg :vel
    :type cl:float
    :initform 0.0)
   (action
    :reader action
    :initarg :action
    :type cl:integer
    :initform 0))
)

(cl:defclass nav_wpt (<nav_wpt>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <nav_wpt>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'nav_wpt)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name navigation-msg:<nav_wpt> is deprecated: use navigation-msg:nav_wpt instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <nav_wpt>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader navigation-msg:header-val is deprecated.  Use navigation-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'north-val :lambda-list '(m))
(cl:defmethod north-val ((m <nav_wpt>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader navigation-msg:north-val is deprecated.  Use navigation-msg:north instead.")
  (north m))

(cl:ensure-generic-function 'east-val :lambda-list '(m))
(cl:defmethod east-val ((m <nav_wpt>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader navigation-msg:east-val is deprecated.  Use navigation-msg:east instead.")
  (east m))

(cl:ensure-generic-function 'vel-val :lambda-list '(m))
(cl:defmethod vel-val ((m <nav_wpt>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader navigation-msg:vel-val is deprecated.  Use navigation-msg:vel instead.")
  (vel m))

(cl:ensure-generic-function 'action-val :lambda-list '(m))
(cl:defmethod action-val ((m <nav_wpt>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader navigation-msg:action-val is deprecated.  Use navigation-msg:action instead.")
  (action m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <nav_wpt>) ostream)
  "Serializes a message object of type '<nav_wpt>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'north))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'east))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'action)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'action)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'action)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'action)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <nav_wpt>) istream)
  "Deserializes a message object of type '<nav_wpt>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'north) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'east) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vel) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'action)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'action)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'action)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'action)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<nav_wpt>)))
  "Returns string type for a message object of type '<nav_wpt>"
  "navigation/nav_wpt")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'nav_wpt)))
  "Returns string type for a message object of type 'nav_wpt"
  "navigation/nav_wpt")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<nav_wpt>)))
  "Returns md5sum for a message object of type '<nav_wpt>"
  "09baa8a35c67a0a28096eac554dd6379")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'nav_wpt)))
  "Returns md5sum for a message object of type 'nav_wpt"
  "09baa8a35c67a0a28096eac554dd6379")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<nav_wpt>)))
  "Returns full string definition for message of type '<nav_wpt>"
  (cl:format cl:nil "Header header~%float64 north~%float64 east~%~%float32 vel~%~%uint32 action~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'nav_wpt)))
  "Returns full string definition for message of type 'nav_wpt"
  (cl:format cl:nil "Header header~%float64 north~%float64 east~%~%float32 vel~%~%uint32 action~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <nav_wpt>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     8
     8
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <nav_wpt>))
  "Converts a ROS message object to a list"
  (cl:list 'nav_wpt
    (cl:cons ':header (header msg))
    (cl:cons ':north (north msg))
    (cl:cons ':east (east msg))
    (cl:cons ':vel (vel msg))
    (cl:cons ':action (action msg))
))
