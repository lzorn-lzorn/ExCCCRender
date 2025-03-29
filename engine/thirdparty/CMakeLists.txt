cmake_minimum_required(VERSION 3.20)
project(thirdparty)

set(ENGINE_THIRDPARTY_CMAKE_DIR ${ExCCCRender_THIRDPARTY_DIR}/cmake)

add_library(${PROJECT_NAME} SHARED dummy.cpp)

include (${ENGINE_THIRDPARTY_CMAKE_DIR}/find_fmt.cmake)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

# include(${ENGINE_THIRDPARTY_CMAKE_DIR}/find_re2.cmake)
