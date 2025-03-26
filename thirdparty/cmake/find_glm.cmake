cmake_minimum_required(VERSION 3.20)

if(NOT TARGET glm)
    file(GLOB_RECURSE
        GLM_HEADERS CONFIGURE_DEPENDS
        "${ExCCCREnder_THIRDPARTY_DIR}/glm/*.h"
        "${ExCCCREnder_THIRDPARTY_DIR}/glm/*.hpp"
    )
    add_library(glm INTERFACE ${GLM_HEADERS})

    # stb 是一个纯头文件库, 使用 INTERFACE tag
    target_include_directories(glm INTERFACE ${GLM_HEADERS})
endif()