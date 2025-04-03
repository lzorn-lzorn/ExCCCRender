cmake_minimum_required(VERSION 3.20)
project(thirdparty)

set(ENGINE_THIRDPARTY_CMAKE_DIR ${ExCCCRender_THIRDPARTY_DIR}/cmake)

add_library(${PROJECT_NAME} SHARED dummy.cpp)

include (${ENGINE_THIRDPARTY_CMAKE_DIR}/find_fmt.cmake)
include (${ENGINE_THIRDPARTY_CMAKE_DIR}/find_range-v3.cmake)


if(WIN32)
# Windows 下的文件
    set(ASSIMP_IMPORT_SHARED_LIB ${ExCCCRender_THIRDPARTY_DIR}/assimp/bin/assimp-vc143-mtd.dll)
    set(ASSIMP_IMPORT_STATIC_LIB ${ExCCCRender_THIRDPARTY_DIR}/assimp/lib/assimp-vc143-mtd.lib)
else()
# Linux 下的路径待补充
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${ExCCCRender_THIRDPARTY_DIR}/assimp/include)

add_library(assimp SHARED IMPORTED)
set_target_properties(assimp PROPERTIES
    IMPORTED_LOCATION ${ASSIMP_IMPORT_SHARED_LIB}
    IMPORTED_IMPLIB ${ASSIMP_IMPORT_STATIC_LIB}
)
target_link_libraries(${PROJECT_NAME} PUBLIC assimp)

# include(${ENGINE_THIRDPARTY_CMAKE_DIR}/find_re2.cmake)
