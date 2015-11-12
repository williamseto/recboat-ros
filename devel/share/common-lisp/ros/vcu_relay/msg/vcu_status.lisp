; Auto-generated. Do not edit!


(cl:in-package vcu_relay-msg)


;//! \htmlinclude vcu_status.msg.html

(cl:defclass <vcu_status> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (ver
    :reader ver
    :initarg :ver
    :type cl:integer
    :initform 0)
   (sec
    :reader sec
    :initarg :sec
    :type cl:integer
    :initform 0)
   (usec
    :reader usec
    :initarg :usec
    :type cl:integer
    :initform 0)
   (state
    :reader state
    :initarg :state
    :type cl:integer
    :initform 0)
   (port_throttle
    :reader port_throttle
    :initarg :port_throttle
    :type cl:float
    :initform 0.0)
   (stbd_throttle
    :reader stbd_throttle
    :initarg :stbd_throttle
    :type cl:float
    :initform 0.0)
   (port_shift
    :reader port_shift
    :initarg :port_shift
    :type cl:float
    :initform 0.0)
   (stbd_shift
    :reader stbd_shift
    :initarg :stbd_shift
    :type cl:float
    :initform 0.0)
   (port_throttle_out
    :reader port_throttle_out
    :initarg :port_throttle_out
    :type cl:float
    :initform 0.0)
   (stbd_throttle_out
    :reader stbd_throttle_out
    :initarg :stbd_throttle_out
    :type cl:float
    :initform 0.0)
   (steer_angle
    :reader steer_angle
    :initarg :steer_angle
    :type cl:float
    :initform 0.0)
   (hci_switch
    :reader hci_switch
    :initarg :hci_switch
    :type cl:fixnum
    :initform 0)
   (port_ind
    :reader port_ind
    :initarg :port_ind
    :type cl:fixnum
    :initform 0)
   (stbd_ind
    :reader stbd_ind
    :initarg :stbd_ind
    :type cl:fixnum
    :initform 0)
   (remote_select
    :reader remote_select
    :initarg :remote_select
    :type cl:fixnum
    :initform 0)
   (autoled
    :reader autoled
    :initarg :autoled
    :type cl:fixnum
    :initform 0)
   (have_ctrl
    :reader have_ctrl
    :initarg :have_ctrl
    :type cl:fixnum
    :initform 0)
   (steer_angle_req
    :reader steer_angle_req
    :initarg :steer_angle_req
    :type cl:float
    :initform 0.0)
   (steer_mode
    :reader steer_mode
    :initarg :steer_mode
    :type cl:integer
    :initform 0)
   (rt_amps
    :reader rt_amps
    :initarg :rt_amps
    :type cl:fixnum
    :initform 0)
   (rt_bamps
    :reader rt_bamps
    :initarg :rt_bamps
    :type cl:fixnum
    :initform 0)
   (rt_ff
    :reader rt_ff
    :initarg :rt_ff
    :type cl:fixnum
    :initform 0)
   (rt_fm
    :reader rt_fm
    :initarg :rt_fm
    :type cl:fixnum
    :initform 0)
   (rt_fs
    :reader rt_fs
    :initarg :rt_fs
    :type cl:fixnum
    :initform 0)
   (rt_power
    :reader rt_power
    :initarg :rt_power
    :type cl:fixnum
    :initform 0)
   (rt_temp
    :reader rt_temp
    :initarg :rt_temp
    :type cl:fixnum
    :initform 0)
   (rt_volt
    :reader rt_volt
    :initarg :rt_volt
    :type cl:fixnum
    :initform 0))
)

(cl:defclass vcu_status (<vcu_status>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <vcu_status>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'vcu_status)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vcu_relay-msg:<vcu_status> is deprecated: use vcu_relay-msg:vcu_status instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <vcu_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:header-val is deprecated.  Use vcu_relay-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'ver-val :lambda-list '(m))
(cl:defmethod ver-val ((m <vcu_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:ver-val is deprecated.  Use vcu_relay-msg:ver instead.")
  (ver m))

(cl:ensure-generic-function 'sec-val :lambda-list '(m))
(cl:defmethod sec-val ((m <vcu_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:sec-val is deprecated.  Use vcu_relay-msg:sec instead.")
  (sec m))

(cl:ensure-generic-function 'usec-val :lambda-list '(m))
(cl:defmethod usec-val ((m <vcu_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:usec-val is deprecated.  Use vcu_relay-msg:usec instead.")
  (usec m))

(cl:ensure-generic-function 'state-val :lambda-list '(m))
(cl:defmethod state-val ((m <vcu_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:state-val is deprecated.  Use vcu_relay-msg:state instead.")
  (state m))

(cl:ensure-generic-function 'port_throttle-val :lambda-list '(m))
(cl:defmethod port_throttle-val ((m <vcu_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:port_throttle-val is deprecated.  Use vcu_relay-msg:port_throttle instead.")
  (port_throttle m))

(cl:ensure-generic-function 'stbd_throttle-val :lambda-list '(m))
(cl:defmethod stbd_throttle-val ((m <vcu_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:stbd_throttle-val is deprecated.  Use vcu_relay-msg:stbd_throttle instead.")
  (stbd_throttle m))

(cl:ensure-generic-function 'port_shift-val :lambda-list '(m))
(cl:defmethod port_shift-val ((m <vcu_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:port_shift-val is deprecated.  Use vcu_relay-msg:port_shift instead.")
  (port_shift m))

(cl:ensure-generic-function 'stbd_shift-val :lambda-list '(m))
(cl:defmethod stbd_shift-val ((m <vcu_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:stbd_shift-val is deprecated.  Use vcu_relay-msg:stbd_shift instead.")
  (stbd_shift m))

(cl:ensure-generic-function 'port_throttle_out-val :lambda-list '(m))
(cl:defmethod port_throttle_out-val ((m <vcu_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:port_throttle_out-val is deprecated.  Use vcu_relay-msg:port_throttle_out instead.")
  (port_throttle_out m))

(cl:ensure-generic-function 'stbd_throttle_out-val :lambda-list '(m))
(cl:defmethod stbd_throttle_out-val ((m <vcu_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:stbd_throttle_out-val is deprecated.  Use vcu_relay-msg:stbd_throttle_out instead.")
  (stbd_throttle_out m))

(cl:ensure-generic-function 'steer_angle-val :lambda-list '(m))
(cl:defmethod steer_angle-val ((m <vcu_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:steer_angle-val is deprecated.  Use vcu_relay-msg:steer_angle instead.")
  (steer_angle m))

(cl:ensure-generic-function 'hci_switch-val :lambda-list '(m))
(cl:defmethod hci_switch-val ((m <vcu_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:hci_switch-val is deprecated.  Use vcu_relay-msg:hci_switch instead.")
  (hci_switch m))

(cl:ensure-generic-function 'port_ind-val :lambda-list '(m))
(cl:defmethod port_ind-val ((m <vcu_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:port_ind-val is deprecated.  Use vcu_relay-msg:port_ind instead.")
  (port_ind m))

(cl:ensure-generic-function 'stbd_ind-val :lambda-list '(m))
(cl:defmethod stbd_ind-val ((m <vcu_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:stbd_ind-val is deprecated.  Use vcu_relay-msg:stbd_ind instead.")
  (stbd_ind m))

(cl:ensure-generic-function 'remote_select-val :lambda-list '(m))
(cl:defmethod remote_select-val ((m <vcu_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:remote_select-val is deprecated.  Use vcu_relay-msg:remote_select instead.")
  (remote_select m))

(cl:ensure-generic-function 'autoled-val :lambda-list '(m))
(cl:defmethod autoled-val ((m <vcu_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:autoled-val is deprecated.  Use vcu_relay-msg:autoled instead.")
  (autoled m))

(cl:ensure-generic-function 'have_ctrl-val :lambda-list '(m))
(cl:defmethod have_ctrl-val ((m <vcu_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:have_ctrl-val is deprecated.  Use vcu_relay-msg:have_ctrl instead.")
  (have_ctrl m))

(cl:ensure-generic-function 'steer_angle_req-val :lambda-list '(m))
(cl:defmethod steer_angle_req-val ((m <vcu_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:steer_angle_req-val is deprecated.  Use vcu_relay-msg:steer_angle_req instead.")
  (steer_angle_req m))

(cl:ensure-generic-function 'steer_mode-val :lambda-list '(m))
(cl:defmethod steer_mode-val ((m <vcu_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:steer_mode-val is deprecated.  Use vcu_relay-msg:steer_mode instead.")
  (steer_mode m))

(cl:ensure-generic-function 'rt_amps-val :lambda-list '(m))
(cl:defmethod rt_amps-val ((m <vcu_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:rt_amps-val is deprecated.  Use vcu_relay-msg:rt_amps instead.")
  (rt_amps m))

(cl:ensure-generic-function 'rt_bamps-val :lambda-list '(m))
(cl:defmethod rt_bamps-val ((m <vcu_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:rt_bamps-val is deprecated.  Use vcu_relay-msg:rt_bamps instead.")
  (rt_bamps m))

(cl:ensure-generic-function 'rt_ff-val :lambda-list '(m))
(cl:defmethod rt_ff-val ((m <vcu_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:rt_ff-val is deprecated.  Use vcu_relay-msg:rt_ff instead.")
  (rt_ff m))

(cl:ensure-generic-function 'rt_fm-val :lambda-list '(m))
(cl:defmethod rt_fm-val ((m <vcu_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:rt_fm-val is deprecated.  Use vcu_relay-msg:rt_fm instead.")
  (rt_fm m))

(cl:ensure-generic-function 'rt_fs-val :lambda-list '(m))
(cl:defmethod rt_fs-val ((m <vcu_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:rt_fs-val is deprecated.  Use vcu_relay-msg:rt_fs instead.")
  (rt_fs m))

(cl:ensure-generic-function 'rt_power-val :lambda-list '(m))
(cl:defmethod rt_power-val ((m <vcu_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:rt_power-val is deprecated.  Use vcu_relay-msg:rt_power instead.")
  (rt_power m))

(cl:ensure-generic-function 'rt_temp-val :lambda-list '(m))
(cl:defmethod rt_temp-val ((m <vcu_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:rt_temp-val is deprecated.  Use vcu_relay-msg:rt_temp instead.")
  (rt_temp m))

(cl:ensure-generic-function 'rt_volt-val :lambda-list '(m))
(cl:defmethod rt_volt-val ((m <vcu_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vcu_relay-msg:rt_volt-val is deprecated.  Use vcu_relay-msg:rt_volt instead.")
  (rt_volt m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <vcu_status>) ostream)
  "Serializes a message object of type '<vcu_status>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'ver)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'ver)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'ver)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'ver)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sec)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'sec)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'sec)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'sec)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'usec)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'usec)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'usec)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'usec)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'state)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'state)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'state)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'state)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'port_throttle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'stbd_throttle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'port_shift))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'stbd_shift))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'port_throttle_out))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'stbd_throttle_out))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'steer_angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'hci_switch)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'port_ind)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'stbd_ind)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'remote_select)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'autoled)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'have_ctrl)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'steer_angle_req))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'steer_mode)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'rt_amps)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'rt_bamps)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'rt_ff)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'rt_fm)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'rt_fs)) ostream)
  (cl:let* ((signed (cl:slot-value msg 'rt_power)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'rt_temp)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'rt_temp)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'rt_volt)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'rt_volt)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <vcu_status>) istream)
  "Deserializes a message object of type '<vcu_status>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'ver)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'ver)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'ver)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'ver)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sec)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'sec)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'sec)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'sec)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'usec)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'usec)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'usec)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'usec)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'state)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'state)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'state)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'state)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'port_throttle) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'stbd_throttle) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'port_shift) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'stbd_shift) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'port_throttle_out) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'stbd_throttle_out) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'steer_angle) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'hci_switch)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'port_ind)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'stbd_ind)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'remote_select)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'autoled)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'have_ctrl)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'steer_angle_req) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'steer_mode) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'rt_amps) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'rt_bamps) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'rt_ff)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'rt_fm)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'rt_fs)) (cl:read-byte istream))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'rt_power) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'rt_temp)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'rt_temp)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'rt_volt)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'rt_volt)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<vcu_status>)))
  "Returns string type for a message object of type '<vcu_status>"
  "vcu_relay/vcu_status")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'vcu_status)))
  "Returns string type for a message object of type 'vcu_status"
  "vcu_relay/vcu_status")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<vcu_status>)))
  "Returns md5sum for a message object of type '<vcu_status>"
  "b5c6dfd3e6cfa86f2afab134f3b7116c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'vcu_status)))
  "Returns md5sum for a message object of type 'vcu_status"
  "b5c6dfd3e6cfa86f2afab134f3b7116c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<vcu_status>)))
  "Returns full string definition for message of type '<vcu_status>"
  (cl:format cl:nil "Header header~%uint32 ver~%uint32 sec~%uint32 usec~%~%uint32 state~%~%# throttle / shift positions read back~%float32 port_throttle~%float32 stbd_throttle~%float32 port_shift~%float32 stbd_shift~%~%# commanded throttle positions~%float32 port_throttle_out~%float32 stbd_throttle_out~%~%# steering angle input~%float32 steer_angle~%~%# inputs~%uint8 hci_switch~%uint8 port_ind~%uint8 stbd_ind~%~%# outputs~%uint8 remote_select~%uint8 autoled~%~%uint8 have_ctrl~%~%float32 steer_angle_req~%int32 steer_mode~%~%# roboteq status~%int16 rt_amps   # motor amps~%int16 rt_bamps  # battery amps~%uint8 rt_ff     # fault flag~%uint8 rt_fm     # runtime status~%uint8 rt_fs     # status flag~%int16 rt_power  # applied power~%uint16 rt_temp  # heatsink temperature~%uint16 rt_volt  # input voltage~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'vcu_status)))
  "Returns full string definition for message of type 'vcu_status"
  (cl:format cl:nil "Header header~%uint32 ver~%uint32 sec~%uint32 usec~%~%uint32 state~%~%# throttle / shift positions read back~%float32 port_throttle~%float32 stbd_throttle~%float32 port_shift~%float32 stbd_shift~%~%# commanded throttle positions~%float32 port_throttle_out~%float32 stbd_throttle_out~%~%# steering angle input~%float32 steer_angle~%~%# inputs~%uint8 hci_switch~%uint8 port_ind~%uint8 stbd_ind~%~%# outputs~%uint8 remote_select~%uint8 autoled~%~%uint8 have_ctrl~%~%float32 steer_angle_req~%int32 steer_mode~%~%# roboteq status~%int16 rt_amps   # motor amps~%int16 rt_bamps  # battery amps~%uint8 rt_ff     # fault flag~%uint8 rt_fm     # runtime status~%uint8 rt_fs     # status flag~%int16 rt_power  # applied power~%uint16 rt_temp  # heatsink temperature~%uint16 rt_volt  # input voltage~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <vcu_status>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     1
     1
     1
     1
     1
     1
     4
     4
     2
     2
     1
     1
     1
     2
     2
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <vcu_status>))
  "Converts a ROS message object to a list"
  (cl:list 'vcu_status
    (cl:cons ':header (header msg))
    (cl:cons ':ver (ver msg))
    (cl:cons ':sec (sec msg))
    (cl:cons ':usec (usec msg))
    (cl:cons ':state (state msg))
    (cl:cons ':port_throttle (port_throttle msg))
    (cl:cons ':stbd_throttle (stbd_throttle msg))
    (cl:cons ':port_shift (port_shift msg))
    (cl:cons ':stbd_shift (stbd_shift msg))
    (cl:cons ':port_throttle_out (port_throttle_out msg))
    (cl:cons ':stbd_throttle_out (stbd_throttle_out msg))
    (cl:cons ':steer_angle (steer_angle msg))
    (cl:cons ':hci_switch (hci_switch msg))
    (cl:cons ':port_ind (port_ind msg))
    (cl:cons ':stbd_ind (stbd_ind msg))
    (cl:cons ':remote_select (remote_select msg))
    (cl:cons ':autoled (autoled msg))
    (cl:cons ':have_ctrl (have_ctrl msg))
    (cl:cons ':steer_angle_req (steer_angle_req msg))
    (cl:cons ':steer_mode (steer_mode msg))
    (cl:cons ':rt_amps (rt_amps msg))
    (cl:cons ':rt_bamps (rt_bamps msg))
    (cl:cons ':rt_ff (rt_ff msg))
    (cl:cons ':rt_fm (rt_fm msg))
    (cl:cons ':rt_fs (rt_fs msg))
    (cl:cons ':rt_power (rt_power msg))
    (cl:cons ':rt_temp (rt_temp msg))
    (cl:cons ':rt_volt (rt_volt msg))
))
