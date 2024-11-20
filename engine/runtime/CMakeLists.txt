
# PackageProject.cmake will be used to make our target installable
set(TARGET_NAME ExCCCRuntime)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- Add source files ----

# Note: globbing sources is considered bad practice as CMake's generators may not detect new files
# automatically. Keep that in mind when changing files, or explicitly mention them here.
file(GLOB_RECURSE HEADER_FILES "*.h" "*.hpp")
file(GLOB_RECURSE SOURCE_FILES "*.cpp")

#source_group(TREE "${ENGINE_ROOT_DIR}/schema" FILES ${SCHEMA_FILES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})


# if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/schema/)
#   file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/schema/" DESTINATION "${CMAKE_BINARY_DIR}/schema")
# endif()

# if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/asset/)
#   file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/asset/" DESTINATION "${CMAKE_BINARY_DIR}/asset")
# endif()
# ---- Create library ----

# Note: for header-only libraries change all PUBLIC flags to INTERFACE and create an interface
# target: add_library(${TARGET_NAME} INTERFACE)
add_library(${TARGET_NAME} ${HEADER_FILES} ${SOURCE_FILES})

set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 20)
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "Engine")

# being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(${TARGET_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->")
target_compile_options(${TARGET_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/WX->")

# Link dependencies    
target_link_libraries(${TARGET_NAME} PUBLIC spdlog::spdlog)
target_link_libraries(${TARGET_NAME} PUBLIC glfw)
target_link_libraries(${TARGET_NAME} PUBLIC imgui)
target_link_libraries(${TARGET_NAME} PUBLIC Vulkan::Vulkan)
target_link_libraries(${TARGET_NAME} PUBLIC assimp::assimp)



target_include_directories(${TARGET_NAME} PUBLIC 
    $<BUILD_INTERFACE:${Vulkan_INCLUDE_DIRS}> # 自动导入 find_package 结果
    $<BUILD_INTERFACE:${VULKAN_SDK}/include>  # 手动补充 Vulkan SDK 的路径
    $<BUILD_INTERFACE:${ENGINE_ROOT_DIR}/runtime>
    $<BUILD_INTERFACE:${THIRD_PARTY_DIR}/glm>
    $<BUILD_INTERFACE:${THIRD_PARTY_DIR}/stb>
    $<BUILD_INTERFACE:${THIRD_PARTY_DIR}/assimp/include>
    $<BUILD_INTERFACE:${THIRD_PARTY_DIR}/spdlog/include>
)






