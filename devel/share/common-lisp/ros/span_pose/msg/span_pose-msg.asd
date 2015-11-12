
(cl:in-package :asdf)

(defsystem "span_pose-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "span_pose" :depends-on ("_package_span_pose"))
    (:file "_package_span_pose" :depends-on ("_package"))
  ))