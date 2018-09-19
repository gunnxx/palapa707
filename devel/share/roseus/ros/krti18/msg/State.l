;; Auto-generated. Do not edit!


(when (boundp 'krti18::State)
  (if (not (find-package "KRTI18"))
    (make-package "KRTI18"))
  (shadow 'State (find-package "KRTI18")))
(unless (find-package "KRTI18::STATE")
  (make-package "KRTI18::STATE"))

(in-package "ROS")
;;//! \htmlinclude State.msg.html


(defclass krti18::State
  :super ros::object
  :slots (_doing_mission ))

(defmethod krti18::State
  (:init
   (&key
    ((:doing_mission __doing_mission) nil)
    )
   (send-super :init)
   (setq _doing_mission __doing_mission)
   self)
  (:doing_mission
   (&optional __doing_mission)
   (if __doing_mission (setq _doing_mission __doing_mission)) _doing_mission)
  (:serialization-length
   ()
   (+
    ;; bool _doing_mission
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _doing_mission
       (if _doing_mission (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _doing_mission
     (setq _doing_mission (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get krti18::State :md5sum-) "c407ee5aa6ad97a1ae9cb0ab26cc8f29")
(setf (get krti18::State :datatype-) "krti18/State")
(setf (get krti18::State :definition-)
      "bool doing_mission

")



(provide :krti18/State "c407ee5aa6ad97a1ae9cb0ab26cc8f29")


