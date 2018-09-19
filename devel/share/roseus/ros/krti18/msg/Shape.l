;; Auto-generated. Do not edit!


(when (boundp 'krti18::Shape)
  (if (not (find-package "KRTI18"))
    (make-package "KRTI18"))
  (shadow 'Shape (find-package "KRTI18")))
(unless (find-package "KRTI18::SHAPE")
  (make-package "KRTI18::SHAPE"))

(in-package "ROS")
;;//! \htmlinclude Shape.msg.html


(defclass krti18::Shape
  :super ros::object
  :slots (_x_obj _y_obj _r_obj ))

(defmethod krti18::Shape
  (:init
   (&key
    ((:x_obj __x_obj) 0)
    ((:y_obj __y_obj) 0)
    ((:r_obj __r_obj) 0)
    )
   (send-super :init)
   (setq _x_obj (round __x_obj))
   (setq _y_obj (round __y_obj))
   (setq _r_obj (round __r_obj))
   self)
  (:x_obj
   (&optional __x_obj)
   (if __x_obj (setq _x_obj __x_obj)) _x_obj)
  (:y_obj
   (&optional __y_obj)
   (if __y_obj (setq _y_obj __y_obj)) _y_obj)
  (:r_obj
   (&optional __r_obj)
   (if __r_obj (setq _r_obj __r_obj)) _r_obj)
  (:serialization-length
   ()
   (+
    ;; uint32 _x_obj
    4
    ;; uint32 _y_obj
    4
    ;; uint32 _r_obj
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint32 _x_obj
       (write-long _x_obj s)
     ;; uint32 _y_obj
       (write-long _y_obj s)
     ;; uint32 _r_obj
       (write-long _r_obj s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint32 _x_obj
     (setq _x_obj (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _y_obj
     (setq _y_obj (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _r_obj
     (setq _r_obj (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get krti18::Shape :md5sum-) "2fbca9de1f9ce5c990e50b663e28ecd0")
(setf (get krti18::Shape :datatype-) "krti18/Shape")
(setf (get krti18::Shape :definition-)
      "uint32 x_obj	    # x coordinates of detected object
uint32 y_obj	    # y coordinates of detected object
uint32 r_obj	    # 		 radius of detected object

")



(provide :krti18/Shape "2fbca9de1f9ce5c990e50b663e28ecd0")


