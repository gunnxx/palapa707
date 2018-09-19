;; Auto-generated. Do not edit!


(when (boundp 'krti18::Ardu)
  (if (not (find-package "KRTI18"))
    (make-package "KRTI18"))
  (shadow 'Ardu (find-package "KRTI18")))
(unless (find-package "KRTI18::ARDU")
  (make-package "KRTI18::ARDU"))

(in-package "ROS")
;;//! \htmlinclude Ardu.msg.html


(defclass krti18::Ardu
  :super ros::object
  :slots (_lidar_alt _switch_status ))

(defmethod krti18::Ardu
  (:init
   (&key
    ((:lidar_alt __lidar_alt) 0.0)
    ((:switch_status __switch_status) nil)
    )
   (send-super :init)
   (setq _lidar_alt (float __lidar_alt))
   (setq _switch_status __switch_status)
   self)
  (:lidar_alt
   (&optional __lidar_alt)
   (if __lidar_alt (setq _lidar_alt __lidar_alt)) _lidar_alt)
  (:switch_status
   (&optional __switch_status)
   (if __switch_status (setq _switch_status __switch_status)) _switch_status)
  (:serialization-length
   ()
   (+
    ;; float32 _lidar_alt
    4
    ;; bool _switch_status
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _lidar_alt
       (sys::poke _lidar_alt (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; bool _switch_status
       (if _switch_status (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _lidar_alt
     (setq _lidar_alt (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; bool _switch_status
     (setq _switch_status (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get krti18::Ardu :md5sum-) "1744afd212cbd2726f4c8b2c0a527f80")
(setf (get krti18::Ardu :datatype-) "krti18/Ardu")
(setf (get krti18::Ardu :definition-)
      "float32 lidar_alt
bool switch_status

")



(provide :krti18/Ardu "1744afd212cbd2726f4c8b2c0a527f80")


