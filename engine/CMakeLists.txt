# aux_source_directory(${ExCCCRender_SOURCE_DIR}/ ENGINE_SOURCES)

message("ExCCCRender_THIRDPARTY_DIR: ${ExCCCRender_THIRDPARTY_DIR}")
file(GLOB_RECURSE
    ENGINE_SOURCES
    ${ExCCCRender_SOURCE_DIR}/*.cpp
    ${ExCCCRender_SOURCE_DIR}/*.c
)

file(GLOB_RECURSE
    ENGINE_HEADERS
    ${ExCCCRender_INCLUDE_DIR}/*.h
    ${ExCCCRender_INCLUDE_DIR}/*.hpp
)

file(GLOB_RECURSE
    ENGINE_INTERFACE
    ${ExCCCRender_INCLUDE_DIR}/*.hpp
)

find_package(Vulkan REQUIRED)
find_package(OpenGL REQUIRED)

# message("ExCCCRender_SOURCE_DIR: ${ExCCCRender_SOURCE_DIR}")
# message("ExCCCRender_INCLUDE_DIR: ${ExCCCRender_INCLUDE_DIR}")
# message("ENGINE_SOURCES: ${ENGINE_SOURCES}")
# message("ENGINE_HEADERS: ${ENGINE_HEADERS}")
# message("PROJECT_NAME: ${PROJECT_NAME}")
add_executable(${PROJECT_NAME} ${ENGINE_SOURCES} ${ENGINE_HEADERS})

add_subdirectory(${ExCCCRender_THIRDPARTY_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC thirdparty)

target_include_directories(${PROJECT_NAME} PUBLIC ${ExCCCRender_INCLUDE_DIR})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_precompile_headers(${PROJECT_NAME} PUBLIC ${ExCCCRender_INCLUDE_DIR}/pch.hpp)

# 链接之后的库
# target_link_libraries(${PROJECT_NAME} PUBLIC
# assimp::assimp
# SDL3::SDL3
# glfw
# )