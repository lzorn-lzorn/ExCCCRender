
aux_source_directory(${ExCCCRender_SOURCE_DIR} ENGINE_SOURCES)

file(GLOB_RECURSE
    ENGINE_HEADERS
    ${ExCCCRender_INCLUDE_DIR}/*.h
    ${ExCCCRender_INCLUDE_DIR}/*.hpp
)

file(GLOB_RECURSE
    ENGINE_INTERFACE
    ${ExCCCRender_INCLUDE_DIR}/*.hpp
)

message("Debug Info ENGINE_HEADERS: ${ENGINE_HEADERS}")
find_package(Vulkan REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} ${ENGINE_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${ENGINE_HEADERS})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_precompile_headers(${PROJECT_NAME} PUBLIC ${ExCCCRender_INCLUDE_DIR}/pch.hpp)

# 链接之后的库
# target_link_libraries(${PROJECT_NAME} PUBLIC
# assimp::assimp
# SDL3::SDL3
# glfw
# )