
(cl:in-package :asdf)

(defsystem "vcu_relay-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "vcu_status" :depends-on ("_package_vcu_status"))
    (:file "_package_vcu_status" :depends-on ("_package"))
    (:file "vcu_cmd_drive" :depends-on ("_package_vcu_cmd_drive"))
    (:file "_package_vcu_cmd_drive" :depends-on ("_package"))
    (:file "vcu_cmd_stop" :depends-on ("_package_vcu_cmd_stop"))
    (:file "_package_vcu_cmd_stop" :depends-on ("_package"))
  ))