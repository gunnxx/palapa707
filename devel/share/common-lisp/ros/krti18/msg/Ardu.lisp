; Auto-generated. Do not edit!


(cl:in-package krti18-msg)


;//! \htmlinclude Ardu.msg.html

(cl:defclass <Ardu> (roslisp-msg-protocol:ros-message)
  ((lidar_alt
    :reader lidar_alt
    :initarg :lidar_alt
    :type cl:float
    :initform 0.0)
   (switch_status
    :reader switch_status
    :initarg :switch_status
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass Ardu (<Ardu>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Ardu>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Ardu)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name krti18-msg:<Ardu> is deprecated: use krti18-msg:Ardu instead.")))

(cl:ensure-generic-function 'lidar_alt-val :lambda-list '(m))
(cl:defmethod lidar_alt-val ((m <Ardu>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader krti18-msg:lidar_alt-val is deprecated.  Use krti18-msg:lidar_alt instead.")
  (lidar_alt m))

(cl:ensure-generic-function 'switch_status-val :lambda-list '(m))
(cl:defmethod switch_status-val ((m <Ardu>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader krti18-msg:switch_status-val is deprecated.  Use krti18-msg:switch_status instead.")
  (switch_status m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Ardu>) ostream)
  "Serializes a message object of type '<Ardu>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'lidar_alt))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'switch_status) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Ardu>) istream)
  "Deserializes a message object of type '<Ardu>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'lidar_alt) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:slot-value msg 'switch_status) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Ardu>)))
  "Returns string type for a message object of type '<Ardu>"
  "krti18/Ardu")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Ardu)))
  "Returns string type for a message object of type 'Ardu"
  "krti18/Ardu")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Ardu>)))
  "Returns md5sum for a message object of type '<Ardu>"
  "1744afd212cbd2726f4c8b2c0a527f80")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Ardu)))
  "Returns md5sum for a message object of type 'Ardu"
  "1744afd212cbd2726f4c8b2c0a527f80")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Ardu>)))
  "Returns full string definition for message of type '<Ardu>"
  (cl:format cl:nil "float32 lidar_alt~%bool switch_status~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Ardu)))
  "Returns full string definition for message of type 'Ardu"
  (cl:format cl:nil "float32 lidar_alt~%bool switch_status~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Ardu>))
  (cl:+ 0
     4
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Ardu>))
  "Converts a ROS message object to a list"
  (cl:list 'Ardu
    (cl:cons ':lidar_alt (lidar_alt msg))
    (cl:cons ':switch_status (switch_status msg))
))
