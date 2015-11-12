; Auto-generated. Do not edit!


(cl:in-package navigation-msg)


;//! \htmlinclude nav_yaw.msg.html

(cl:defclass <nav_yaw> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (yaw
    :reader yaw
    :initarg :yaw
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

(cl:defclass nav_yaw (<nav_yaw>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <nav_yaw>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'nav_yaw)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name navigation-msg:<nav_yaw> is deprecated: use navigation-msg:nav_yaw instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <nav_yaw>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader navigation-msg:header-val is deprecated.  Use navigation-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'yaw-val :lambda-list '(m))
(cl:defmethod yaw-val ((m <nav_yaw>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader navigation-msg:yaw-val is deprecated.  Use navigation-msg:yaw instead.")
  (yaw m))

(cl:ensure-generic-function 'vel-val :lambda-list '(m))
(cl:defmethod vel-val ((m <nav_yaw>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader navigation-msg:vel-val is deprecated.  Use navigation-msg:vel instead.")
  (vel m))

(cl:ensure-generic-function 'action-val :lambda-list '(m))
(cl:defmethod action-val ((m <nav_yaw>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader navigation-msg:action-val is deprecated.  Use navigation-msg:action instead.")
  (action m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <nav_yaw>) ostream)
  "Serializes a message object of type '<nav_yaw>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'yaw))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <nav_yaw>) istream)
  "Deserializes a message object of type '<nav_yaw>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'yaw) (roslisp-utils:decode-single-float-bits bits)))
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<nav_yaw>)))
  "Returns string type for a message object of type '<nav_yaw>"
  "navigation/nav_yaw")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'nav_yaw)))
  "Returns string type for a message object of type 'nav_yaw"
  "navigation/nav_yaw")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<nav_yaw>)))
  "Returns md5sum for a message object of type '<nav_yaw>"
  "335e425fcd3dfa1c1439310c7bb41472")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'nav_yaw)))
  "Returns md5sum for a message object of type 'nav_yaw"
  "335e425fcd3dfa1c1439310c7bb41472")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<nav_yaw>)))
  "Returns full string definition for message of type '<nav_yaw>"
  (cl:format cl:nil "Header header~%float32 yaw~%float32 vel~%~%uint32 action~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'nav_yaw)))
  "Returns full string definition for message of type 'nav_yaw"
  (cl:format cl:nil "Header header~%float32 yaw~%float32 vel~%~%uint32 action~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <nav_yaw>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <nav_yaw>))
  "Converts a ROS message object to a list"
  (cl:list 'nav_yaw
    (cl:cons ':header (header msg))
    (cl:cons ':yaw (yaw msg))
    (cl:cons ':vel (vel msg))
    (cl:cons ':action (action msg))
))
