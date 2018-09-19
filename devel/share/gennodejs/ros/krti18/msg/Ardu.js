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

class Ardu {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.lidar_alt = null;
      this.switch_status = null;
    }
    else {
      if (initObj.hasOwnProperty('lidar_alt')) {
        this.lidar_alt = initObj.lidar_alt
      }
      else {
        this.lidar_alt = 0.0;
      }
      if (initObj.hasOwnProperty('switch_status')) {
        this.switch_status = initObj.switch_status
      }
      else {
        this.switch_status = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Ardu
    // Serialize message field [lidar_alt]
    bufferOffset = _serializer.float32(obj.lidar_alt, buffer, bufferOffset);
    // Serialize message field [switch_status]
    bufferOffset = _serializer.bool(obj.switch_status, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Ardu
    let len;
    let data = new Ardu(null);
    // Deserialize message field [lidar_alt]
    data.lidar_alt = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [switch_status]
    data.switch_status = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 5;
  }

  static datatype() {
    // Returns string type for a message object
    return 'krti18/Ardu';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '1744afd212cbd2726f4c8b2c0a527f80';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 lidar_alt
    bool switch_status
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Ardu(null);
    if (msg.lidar_alt !== undefined) {
      resolved.lidar_alt = msg.lidar_alt;
    }
    else {
      resolved.lidar_alt = 0.0
    }

    if (msg.switch_status !== undefined) {
      resolved.switch_status = msg.switch_status;
    }
    else {
      resolved.switch_status = false
    }

    return resolved;
    }
};

module.exports = Ardu;
