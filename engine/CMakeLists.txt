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

if(WIN32)
    find_package(Vulkan REQUIRED)
    find_package(OpenGL REQUIRED)
elseif(APPLE)
    message("APPLE")
    # 添加metal
    find_library(MATAL_LIBRARY Metal)
    find_library(FOUNDATION_LIBRARY Foundation)
    find_library(QUARTZCORE_LIBRART QuartzCore)
elseif(UNIX)
    find_package(Vulkan REQUIRED)
    find_package(OpenGL REQUIRED)
else()
    message("UNKONW Platform")
endif()    


# message("ExCCCRender_SOURCE_DIR: ${ExCCCRender_SOURCE_DIR}")
# message("ExCCCRender_INCLUDE_DIR: ${ExCCCRender_INCLUDE_DIR}")
message("ENGINE_SOURCES: ${ENGINE_SOURCES}")

# message("ENGINE_HEADERS: ${ENGINE_HEADERS}")
# message("PROJECT_NAME: ${PROJECT_NAME}")
add_executable(${PROJECT_NAME} ${ENGINE_SOURCES} ${ENGINE_HEADERS})

if(APPLE)
    target_link_libraries(${PROJECT_NAME}
        ${METAL_LIBRARY}
        ${FOUNDATION_LIBRARY}
        ${QUARTZCORE_LIBRARY}
    )

    file(GLOB_RECURSE METAL_SHADER_FILES ${ExCCCREND_SOURCE_DIR}/*.metal)
    set(METAL_AIR_FILES "")

    #编译 .metal 为 .air
    foreach()
        get_filename_component(name ${file} NAME_WE)
        set(output "${CMAKE_BINARY_DIR}/${name}.air")
        message("Cmake_binary_dir: ${CMAKE_BINARY_DIR}")
        message("ExCCCRender Binary dir: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")  
        add_custom_command(
            OUTPUT ${output}
            COMMAND xcrun -sdk macosx metal -c ${file} -o ${output}
            DEPENDS ${file}
        )
        list(APPEND METAL_AIR_FILES ${output})
    endforeach()
    
    # 打包为 .metallib
    add_custom_command(
        OUTPUT "${CMAKE_BINARY_DIR}/default.metallib"
        COMMAND xcrun -sdk macosx metallib ${METAL_AIR_FILES} -o default.metallib
        DEPENDS ${METAL_AIR_FILES}
    )
    add_custom_target(compile_metal ALL DEPENDS default.metallib)
    target_include_directories(${PROJECT_NAME} PUBLIC "include/metal_cpp")
endif()



add_subdirectory(${ExCCCRender_THIRDPARTY_DIR})

target_include_directories(${PROJECT_NAME} PUBLIC ${ExCCCRender_INCLUDE_DIR})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_precompile_headers(${PROJECT_NAME} PUBLIC ${ExCCCRender_INCLUDE_DIR}/pch.hpp)
