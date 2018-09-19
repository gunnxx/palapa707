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

class State {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.doing_mission = null;
    }
    else {
      if (initObj.hasOwnProperty('doing_mission')) {
        this.doing_mission = initObj.doing_mission
      }
      else {
        this.doing_mission = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type State
    // Serialize message field [doing_mission]
    bufferOffset = _serializer.bool(obj.doing_mission, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type State
    let len;
    let data = new State(null);
    // Deserialize message field [doing_mission]
    data.doing_mission = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a message object
    return 'krti18/State';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c407ee5aa6ad97a1ae9cb0ab26cc8f29';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool doing_mission
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new State(null);
    if (msg.doing_mission !== undefined) {
      resolved.doing_mission = msg.doing_mission;
    }
    else {
      resolved.doing_mission = false
    }

    return resolved;
    }
};

module.exports = State;
