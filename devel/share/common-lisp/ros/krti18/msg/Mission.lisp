; Auto-generated. Do not edit!


(cl:in-package krti18-msg)


;//! \htmlinclude Mission.msg.html

(cl:defclass <Mission> (roslisp-msg-protocol:ros-message)
  ((mission_type
    :reader mission_type
    :initarg :mission_type
    :type cl:fixnum
    :initform 0))
)

(cl:defclass Mission (<Mission>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Mission>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Mission)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name krti18-msg:<Mission> is deprecated: use krti18-msg:Mission instead.")))

(cl:ensure-generic-function 'mission_type-val :lambda-list '(m))
(cl:defmethod mission_type-val ((m <Mission>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader krti18-msg:mission_type-val is deprecated.  Use krti18-msg:mission_type instead.")
  (mission_type m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Mission>) ostream)
  "Serializes a message object of type '<Mission>"
  (cl:let* ((signed (cl:slot-value msg 'mission_type)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Mission>) istream)
  "Deserializes a message object of type '<Mission>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'mission_type) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Mission>)))
  "Returns string type for a message object of type '<Mission>"
  "krti18/Mission")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Mission)))
  "Returns string type for a message object of type 'Mission"
  "krti18/Mission")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Mission>)))
  "Returns md5sum for a message object of type '<Mission>"
  "9afd8c5819bc00a1915a5527b744824a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Mission)))
  "Returns md5sum for a message object of type 'Mission"
  "9afd8c5819bc00a1915a5527b744824a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Mission>)))
  "Returns full string definition for message of type '<Mission>"
  (cl:format cl:nil "int8 mission_type~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Mission)))
  "Returns full string definition for message of type 'Mission"
  (cl:format cl:nil "int8 mission_type~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Mission>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Mission>))
  "Converts a ROS message object to a list"
  (cl:list 'Mission
    (cl:cons ':mission_type (mission_type msg))
))
