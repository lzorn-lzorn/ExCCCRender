cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

project(ExCCCRender VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS OFF)

add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

# 针对 GCC 或 Clang
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wno-error -Wno-deprecated-declarations -Wdeprecated-non-prototype)
endif()
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wno-error -Wno-deprecated-declarations -Wdeprecated-non-prototype)
endif()


# ---- Include guards ----
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")# 针对 MSVC
    add_compile_options(/wd4996) # 4996 对应 _CRT_SECURE_NO_WARNINGS 的警告
endif()


set(ExCCCRender_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_INSTALL_PREFIX "${ExCCCRender_ROOT_DIR}/bin")
set(BINARY_ROOT_DIR "${CMAKE_INSTALL_PREFIX}/")


add_subdirectory(engine)