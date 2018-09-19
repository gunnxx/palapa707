
(cl:in-package :asdf)

(defsystem "krti18-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Ardu" :depends-on ("_package_Ardu"))
    (:file "_package_Ardu" :depends-on ("_package"))
    (:file "Mission" :depends-on ("_package_Mission"))
    (:file "_package_Mission" :depends-on ("_package"))
    (:file "Shape" :depends-on ("_package_Shape"))
    (:file "_package_Shape" :depends-on ("_package"))
    (:file "State" :depends-on ("_package_State"))
    (:file "_package_State" :depends-on ("_package"))
  ))