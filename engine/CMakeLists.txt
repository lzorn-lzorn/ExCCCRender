set(ENGINE_ROOT_DIR "${PICCOLO_ROOT_DIR}/engine")
set(THIRD_PARTY_DIR "${ENGINE_ROOT_DIR}/thirdparty")
set(ENGINE_ASSET_DIR "/asset")

find_package(Vulkan REQUIRED)
find_package(OpenGL REQUIRED)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options("/MP")
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT PiccoloEditor)
endif()

add_subdirectory(thirdparty)
add_subdirectory(runtime)
add_subdirectory(editor)
