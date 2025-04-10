cmake_minimum_required(VERSION 3.20)

set(ENGINE_THIRDPARTY_CMAKE_DIR ${ExCCCRender_THIRDPARTY_DIR}/cmake)

message(${PROJECT_NAME})

# add_library(${PROJECT_NAME} SHARED dummy.cpp)
include(${ENGINE_THIRDPARTY_CMAKE_DIR}/find_fmt.cmake)
include(${ENGINE_THIRDPARTY_CMAKE_DIR}/find_range-v3.cmake)
include(${ENGINE_THIRDPARTY_CMAKE_DIR}/find_assimp.cmake)

# include(${ENGINE_THIRDPARTY_CMAKE_DIR}/find_re2.cmake)
