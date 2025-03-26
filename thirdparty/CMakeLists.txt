cmake_minimum_required(VERSION 3.10)
project(thirdparty)

set(ENGINE_THIRDPARTY_CMAKE_DIR ${ExCCCRender_THIRDPARTY_DIR}/cmake)
file(GLOB_RECURSE
    ENGINE_THIRDPPARTY_INCLUDE
    ${ExCCCRender_THIRDPARTY_DIR}/*.h
    ${ExCCCRender_THIRDPARTY_DIR}/*.hpp
)

add_library(thirdparty SHARED dummy.cpp)
target_include_directories(thirdparty PUBLIC ${ENGINE_THIRDPPARTY_INCLUDE})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

# include(${ENGINE_THIRDPARTY_CMAKE_DIR}/find_re2.cmake)
