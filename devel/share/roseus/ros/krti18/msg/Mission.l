;; Auto-generated. Do not edit!


(when (boundp 'krti18::Mission)
  (if (not (find-package "KRTI18"))
    (make-package "KRTI18"))
  (shadow 'Mission (find-package "KRTI18")))
(unless (find-package "KRTI18::MISSION")
  (make-package "KRTI18::MISSION"))

(in-package "ROS")
;;//! \htmlinclude Mission.msg.html


(defclass krti18::Mission
  :super ros::object
  :slots (_mission_type ))

(defmethod krti18::Mission
  (:init
   (&key
    ((:mission_type __mission_type) 0)
    )
   (send-super :init)
   (setq _mission_type (round __mission_type))
   self)
  (:mission_type
   (&optional __mission_type)
   (if __mission_type (setq _mission_type __mission_type)) _mission_type)
  (:serialization-length
   ()
   (+
    ;; int8 _mission_type
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _mission_type
       (write-byte _mission_type s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _mission_type
     (setq _mission_type (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _mission_type 127) (setq _mission_type (- _mission_type 256)))
   ;;
   self)
  )

(setf (get krti18::Mission :md5sum-) "9afd8c5819bc00a1915a5527b744824a")
(setf (get krti18::Mission :datatype-) "krti18/Mission")
(setf (get krti18::Mission :definition-)
      "int8 mission_type

")



(provide :krti18/Mission "9afd8c5819bc00a1915a5527b744824a")


