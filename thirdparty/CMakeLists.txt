cmake_minimum_required(VERSION 3.20)
project(thirdparty)

set(ENGINE_THIRDPARTY_CMAKE_DIR ${ExCCCRender_THIRDPARTY_DIR}/cmake)

add_library(${PROJECT_NAME} SHARED dummy.cpp)

add_subdirectory(${ExCCCRender_THIRDPARTY_DIR}/fmt)
target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt)
target_include_directories(${PROJECT_NAME} PUBLIC ${ExCCCRender_THIRDPARTY_DIR})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

# include(${ENGINE_THIRDPARTY_CMAKE_DIR}/find_re2.cmake)
