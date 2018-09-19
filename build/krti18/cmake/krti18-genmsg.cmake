# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "krti18: 4 messages, 0 services")

set(MSG_I_FLAGS "-Ikrti18:/home/ubuntu/Documents/auav/palapa707/src/krti18/msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(krti18_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Ardu.msg" NAME_WE)
add_custom_target(_krti18_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "krti18" "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Ardu.msg" ""
)

get_filename_component(_filename "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/State.msg" NAME_WE)
add_custom_target(_krti18_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "krti18" "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/State.msg" ""
)

get_filename_component(_filename "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Mission.msg" NAME_WE)
add_custom_target(_krti18_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "krti18" "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Mission.msg" ""
)

get_filename_component(_filename "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Shape.msg" NAME_WE)
add_custom_target(_krti18_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "krti18" "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Shape.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(krti18
  "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/State.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/krti18
)
_generate_msg_cpp(krti18
  "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Shape.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/krti18
)
_generate_msg_cpp(krti18
  "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Mission.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/krti18
)
_generate_msg_cpp(krti18
  "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Ardu.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/krti18
)

### Generating Services

### Generating Module File
_generate_module_cpp(krti18
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/krti18
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(krti18_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(krti18_generate_messages krti18_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Ardu.msg" NAME_WE)
add_dependencies(krti18_generate_messages_cpp _krti18_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/State.msg" NAME_WE)
add_dependencies(krti18_generate_messages_cpp _krti18_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Mission.msg" NAME_WE)
add_dependencies(krti18_generate_messages_cpp _krti18_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Shape.msg" NAME_WE)
add_dependencies(krti18_generate_messages_cpp _krti18_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(krti18_gencpp)
add_dependencies(krti18_gencpp krti18_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS krti18_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(krti18
  "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/State.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/krti18
)
_generate_msg_eus(krti18
  "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Shape.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/krti18
)
_generate_msg_eus(krti18
  "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Mission.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/krti18
)
_generate_msg_eus(krti18
  "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Ardu.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/krti18
)

### Generating Services

### Generating Module File
_generate_module_eus(krti18
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/krti18
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(krti18_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(krti18_generate_messages krti18_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Ardu.msg" NAME_WE)
add_dependencies(krti18_generate_messages_eus _krti18_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/State.msg" NAME_WE)
add_dependencies(krti18_generate_messages_eus _krti18_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Mission.msg" NAME_WE)
add_dependencies(krti18_generate_messages_eus _krti18_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Shape.msg" NAME_WE)
add_dependencies(krti18_generate_messages_eus _krti18_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(krti18_geneus)
add_dependencies(krti18_geneus krti18_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS krti18_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(krti18
  "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/State.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/krti18
)
_generate_msg_lisp(krti18
  "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Shape.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/krti18
)
_generate_msg_lisp(krti18
  "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Mission.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/krti18
)
_generate_msg_lisp(krti18
  "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Ardu.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/krti18
)

### Generating Services

### Generating Module File
_generate_module_lisp(krti18
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/krti18
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(krti18_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(krti18_generate_messages krti18_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Ardu.msg" NAME_WE)
add_dependencies(krti18_generate_messages_lisp _krti18_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/State.msg" NAME_WE)
add_dependencies(krti18_generate_messages_lisp _krti18_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Mission.msg" NAME_WE)
add_dependencies(krti18_generate_messages_lisp _krti18_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Shape.msg" NAME_WE)
add_dependencies(krti18_generate_messages_lisp _krti18_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(krti18_genlisp)
add_dependencies(krti18_genlisp krti18_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS krti18_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(krti18
  "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/State.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/krti18
)
_generate_msg_nodejs(krti18
  "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Shape.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/krti18
)
_generate_msg_nodejs(krti18
  "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Mission.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/krti18
)
_generate_msg_nodejs(krti18
  "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Ardu.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/krti18
)

### Generating Services

### Generating Module File
_generate_module_nodejs(krti18
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/krti18
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(krti18_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(krti18_generate_messages krti18_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Ardu.msg" NAME_WE)
add_dependencies(krti18_generate_messages_nodejs _krti18_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/State.msg" NAME_WE)
add_dependencies(krti18_generate_messages_nodejs _krti18_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Mission.msg" NAME_WE)
add_dependencies(krti18_generate_messages_nodejs _krti18_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Shape.msg" NAME_WE)
add_dependencies(krti18_generate_messages_nodejs _krti18_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(krti18_gennodejs)
add_dependencies(krti18_gennodejs krti18_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS krti18_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(krti18
  "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/State.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/krti18
)
_generate_msg_py(krti18
  "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Shape.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/krti18
)
_generate_msg_py(krti18
  "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Mission.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/krti18
)
_generate_msg_py(krti18
  "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Ardu.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/krti18
)

### Generating Services

### Generating Module File
_generate_module_py(krti18
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/krti18
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(krti18_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(krti18_generate_messages krti18_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Ardu.msg" NAME_WE)
add_dependencies(krti18_generate_messages_py _krti18_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/State.msg" NAME_WE)
add_dependencies(krti18_generate_messages_py _krti18_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Mission.msg" NAME_WE)
add_dependencies(krti18_generate_messages_py _krti18_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ubuntu/Documents/auav/palapa707/src/krti18/msg/Shape.msg" NAME_WE)
add_dependencies(krti18_generate_messages_py _krti18_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(krti18_genpy)
add_dependencies(krti18_genpy krti18_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS krti18_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/krti18)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/krti18
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(krti18_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/krti18)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/krti18
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(krti18_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/krti18)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/krti18
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(krti18_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/krti18)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/krti18
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(krti18_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/krti18)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/krti18\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/krti18
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(krti18_generate_messages_py std_msgs_generate_messages_py)
endif()
