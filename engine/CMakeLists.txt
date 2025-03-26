aux_source_directory(./src ENGINE_SOURCES)
file(GLOB_RECURSE
    ENGINE_HEADERS
    ${ExCCCRender_INCLUDE_DIR}/*.h
    ${ExCCCRender_INCLUDE_DIR}/*.hpp
)
file(GLOB_RECURSE
    ENGINE_INTERFACES
    ${ENGINE_DIR}/*.hpp
)

message("Debug Info Src:${ENGINE_SOURCES}")
message("Debug Info Include:${ENGINE_HEADERS}")

find_package(Vulkan REQUIRED)
find_package(OpenGL REQUIRED)

# 为了Test 可以将整个引擎打包为静态链接库, 在Test/ 进行测试
# add_library(${PROJECT_NAME} STATIC ${ENGINE_SOURCES})
add_executable(${PROJECT_NAME} PUBLIC ${ENGINE_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${ENGINE_HEADERS})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_precompile_headers(${PROJECT_NAME} PUBLIC ./include/pch.hpp)
