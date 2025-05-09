cmake_minimum_required(VERSION 3.20)

project(
  ExCCCRender
  LANGUAGES CXX C
  DESCRIPTION "ExCCCRender!"
  VERSION 0.1.0
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS OFF)

# 启用生成 compile_commands.json
set(EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

# 设置全局的变量:
# 项目路径
set(ExCCCRender_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

# 引擎路径
set(ExCCCRender_ENGINE_DIR "${ExCCCRender_ROOT_DIR}/engine")

# Include路径
set(ExCCCRender_INCLUDE_DIR "${ExCCCRender_ENGINE_DIR}/include")

# Source路径
set(ExCCCRender_SOURCE_DIR "${ExCCCRender_ENGINE_DIR}/src")

# 第三方库路径
set(ExCCCRender_THIRDPARTY_DIR "${ExCCCRender_ENGINE_DIR}/thirdparty")

# 设置可执行文件的输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${ExCCCRender_ROOT_DIR}/bin")

# 设置静态库输出路径
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lib")

# 设置动态库输出路径
# Windows 下dll须在exe同级目录
if(WIN32)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${ExCCCRender_ROOT_DIR}/bin")
else()
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lib")
endif()

add_subdirectory(engine)
