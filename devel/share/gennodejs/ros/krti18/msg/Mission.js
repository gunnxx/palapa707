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

class Mission {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.mission_type = null;
    }
    else {
      if (initObj.hasOwnProperty('mission_type')) {
        this.mission_type = initObj.mission_type
      }
      else {
        this.mission_type = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Mission
    // Serialize message field [mission_type]
    bufferOffset = _serializer.int8(obj.mission_type, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Mission
    let len;
    let data = new Mission(null);
    // Deserialize message field [mission_type]
    data.mission_type = _deserializer.int8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a message object
    return 'krti18/Mission';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '9afd8c5819bc00a1915a5527b744824a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int8 mission_type
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Mission(null);
    if (msg.mission_type !== undefined) {
      resolved.mission_type = msg.mission_type;
    }
    else {
      resolved.mission_type = 0
    }

    return resolved;
    }
};

module.exports = Mission;
