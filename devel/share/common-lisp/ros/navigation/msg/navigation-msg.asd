
(cl:in-package :asdf)

(defsystem "navigation-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "nav_yaw" :depends-on ("_package_nav_yaw"))
    (:file "_package_nav_yaw" :depends-on ("_package"))
    (:file "nav_status" :depends-on ("_package_nav_status"))
    (:file "_package_nav_status" :depends-on ("_package"))
    (:file "nav_wpt" :depends-on ("_package_nav_wpt"))
    (:file "_package_nav_wpt" :depends-on ("_package"))
    (:file "nav_cmd" :depends-on ("_package_nav_cmd"))
    (:file "_package_nav_cmd" :depends-on ("_package"))
  ))