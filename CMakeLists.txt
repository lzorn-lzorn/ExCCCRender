cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(
  ExCCCRender
  LANGUAGES CXX C
  DESCRIPTION "ExCCC Render!"
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
set(ENGINE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/engine")

# Include路径
set(ExCCCRender_INCLUDE_DIR "${ExCCCRender_ROOT_DIR}/engine/include")

# Source路径
set(ExCCCRender_SOURCE_DIR "${ExCCCRender_ROOT_DIR}/engine/src")

# 第三方库路径
set(ExCCCREnder_THIRDPARTY_DIR "${ExCCCRender_ROOT_DIR}/thirdparty")

add_subdirectory(engine)
add_subdirectory(thirdparty)
