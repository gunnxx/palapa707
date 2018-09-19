; Auto-generated. Do not edit!


(cl:in-package krti18-msg)


;//! \htmlinclude Shape.msg.html

(cl:defclass <Shape> (roslisp-msg-protocol:ros-message)
  ((x_obj
    :reader x_obj
    :initarg :x_obj
    :type cl:integer
    :initform 0)
   (y_obj
    :reader y_obj
    :initarg :y_obj
    :type cl:integer
    :initform 0)
   (r_obj
    :reader r_obj
    :initarg :r_obj
    :type cl:integer
    :initform 0))
)

(cl:defclass Shape (<Shape>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Shape>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Shape)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name krti18-msg:<Shape> is deprecated: use krti18-msg:Shape instead.")))

(cl:ensure-generic-function 'x_obj-val :lambda-list '(m))
(cl:defmethod x_obj-val ((m <Shape>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader krti18-msg:x_obj-val is deprecated.  Use krti18-msg:x_obj instead.")
  (x_obj m))

(cl:ensure-generic-function 'y_obj-val :lambda-list '(m))
(cl:defmethod y_obj-val ((m <Shape>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader krti18-msg:y_obj-val is deprecated.  Use krti18-msg:y_obj instead.")
  (y_obj m))

(cl:ensure-generic-function 'r_obj-val :lambda-list '(m))
(cl:defmethod r_obj-val ((m <Shape>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader krti18-msg:r_obj-val is deprecated.  Use krti18-msg:r_obj instead.")
  (r_obj m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Shape>) ostream)
  "Serializes a message object of type '<Shape>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'x_obj)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'x_obj)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'x_obj)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'x_obj)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'y_obj)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'y_obj)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'y_obj)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'y_obj)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'r_obj)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'r_obj)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'r_obj)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'r_obj)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Shape>) istream)
  "Deserializes a message object of type '<Shape>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'x_obj)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'x_obj)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'x_obj)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'x_obj)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'y_obj)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'y_obj)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'y_obj)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'y_obj)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'r_obj)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'r_obj)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'r_obj)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'r_obj)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Shape>)))
  "Returns string type for a message object of type '<Shape>"
  "krti18/Shape")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Shape)))
  "Returns string type for a message object of type 'Shape"
  "krti18/Shape")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Shape>)))
  "Returns md5sum for a message object of type '<Shape>"
  "2fbca9de1f9ce5c990e50b663e28ecd0")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Shape)))
  "Returns md5sum for a message object of type 'Shape"
  "2fbca9de1f9ce5c990e50b663e28ecd0")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Shape>)))
  "Returns full string definition for message of type '<Shape>"
  (cl:format cl:nil "uint32 x_obj	    # x coordinates of detected object~%uint32 y_obj	    # y coordinates of detected object~%uint32 r_obj	    # 		 radius of detected object~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Shape)))
  "Returns full string definition for message of type 'Shape"
  (cl:format cl:nil "uint32 x_obj	    # x coordinates of detected object~%uint32 y_obj	    # y coordinates of detected object~%uint32 r_obj	    # 		 radius of detected object~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Shape>))
  (cl:+ 0
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Shape>))
  "Converts a ROS message object to a list"
  (cl:list 'Shape
    (cl:cons ':x_obj (x_obj msg))
    (cl:cons ':y_obj (y_obj msg))
    (cl:cons ':r_obj (r_obj msg))
))
