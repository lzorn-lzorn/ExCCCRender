set(imgui_SOURCE_DIR_ ${CMAKE_CURRENT_SOURCE_DIR}/imgui)

# 收集 ImGui 源文件和特定后端实现
file(GLOB imgui_sources CONFIGURE_DEPENDS "${imgui_SOURCE_DIR_}/*.cpp")
file(GLOB imgui_impl CONFIGURE_DEPENDS  
    "${imgui_SOURCE_DIR_}/backends/imgui_impl_glfw.cpp" 
    "${imgui_SOURCE_DIR_}/backends/imgui_impl_glfw.h"
    "${imgui_SOURCE_DIR_}/backends/imgui_impl_vulkan.cpp" 
    "${imgui_SOURCE_DIR_}/backends/imgui_impl_vulkan.h"
    "${imgui_SOURCE_DIR_}/backends/imgui_impl_opengl3.cpp" 
    "${imgui_SOURCE_DIR_}/backends/imgui_impl_opengl3.h"
)

# 创建 imgui 库
add_library(imgui STATIC ${imgui_sources} ${imgui_impl})

# 包含路径设置
target_include_directories(imgui PUBLIC 
    $<BUILD_INTERFACE:${imgui_SOURCE_DIR_}>
    $<BUILD_INTERFACE:${Vulkan_INCLUDE_DIRS}>  # Vulkan 自动提供的 include 路径
)

# 链接库设置
find_package(Vulkan REQUIRED)  # 自动检测 Vulkan SDK
target_link_libraries(imgui PUBLIC glfw Vulkan::Vulkan OpenGL::GL)  # 链接 Vulkan 和 OpenGL
