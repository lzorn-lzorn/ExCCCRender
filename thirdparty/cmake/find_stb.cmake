cmake_minimum_required(VERSION 3.20)

if(NOT TARGET stb)
    file(GLOB_RECURSE
        STB_HEADERS CONFIGURE_DEPENDS
        "${ExCCCRender_THIRDPARTY_DIR}/stb/*.h"
        "${ExCCCRender_THIRDPARTY_DIR}/stb/*.hpp"
    )
    add_library(stb INTERFACE ${STB_HEADERS})

    # stb 是一个纯头文件库, 使用 INTERFACE tag
    target_include_directories(stb INTERFACE ${STB_HEADERS})
endif()