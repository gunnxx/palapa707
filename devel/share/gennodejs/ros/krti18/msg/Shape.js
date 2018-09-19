// Auto-generated. Do not edit!

// (in-package krti18.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class Shape {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.x_obj = null;
      this.y_obj = null;
      this.r_obj = null;
    }
    else {
      if (initObj.hasOwnProperty('x_obj')) {
        this.x_obj = initObj.x_obj
      }
      else {
        this.x_obj = 0;
      }
      if (initObj.hasOwnProperty('y_obj')) {
        this.y_obj = initObj.y_obj
      }
      else {
        this.y_obj = 0;
      }
      if (initObj.hasOwnProperty('r_obj')) {
        this.r_obj = initObj.r_obj
      }
      else {
        this.r_obj = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Shape
    // Serialize message field [x_obj]
    bufferOffset = _serializer.uint32(obj.x_obj, buffer, bufferOffset);
    // Serialize message field [y_obj]
    bufferOffset = _serializer.uint32(obj.y_obj, buffer, bufferOffset);
    // Serialize message field [r_obj]
    bufferOffset = _serializer.uint32(obj.r_obj, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Shape
    let len;
    let data = new Shape(null);
    // Deserialize message field [x_obj]
    data.x_obj = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [y_obj]
    data.y_obj = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [r_obj]
    data.r_obj = _deserializer.uint32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 12;
  }

  static datatype() {
    // Returns string type for a message object
    return 'krti18/Shape';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '2fbca9de1f9ce5c990e50b663e28ecd0';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint32 x_obj	    # x coordinates of detected object
    uint32 y_obj	    # y coordinates of detected object
    uint32 r_obj	    # 		 radius of detected object
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Shape(null);
    if (msg.x_obj !== undefined) {
      resolved.x_obj = msg.x_obj;
    }
    else {
      resolved.x_obj = 0
    }

    if (msg.y_obj !== undefined) {
      resolved.y_obj = msg.y_obj;
    }
    else {
      resolved.y_obj = 0
    }

    if (msg.r_obj !== undefined) {
      resolved.r_obj = msg.r_obj;
    }
    else {
      resolved.r_obj = 0
    }

    return resolved;
    }
};

module.exports = Shape;
