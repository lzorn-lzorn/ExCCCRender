set(TARGET_NAME ExCCCEditor)

file(GLOB EDITOR_HEADERS CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB EDITOR_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

# 用于IDE的分组管理
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${EDITOR_HEADERS} ${EDITOR_SOURCES} ${EDITOR_RESOURCE})

add_executable(${TARGET_NAME} ${EDITOR_HEADERS} ${EDITOR_SOURCES})

target_include_directories(${TARGET_NAME} PUBLIC 
    $<BUILD_INTERFACE:${Vulkan_INCLUDE_DIRS}> # 自动导入 find_package 结果
    $<BUILD_INTERFACE:${VULKAN_SDK}/include>  # 手动补充 Vulkan SDK 的路径
    $<BUILD_INTERFACE:${ENGINE_ROOT_DIR}>
    $<BUILD_INTERFACE:${ENGINE_ROOT_DIR}/runtime>
    $<BUILD_INTERFACE:${THIRD_PARTY_DIR}/glm>
    $<BUILD_INTERFACE:${THIRD_PARTY_DIR}/glfw>
    $<BUILD_INTERFACE:${THIRD_PARTY_DIR}/stb>
    $<BUILD_INTERFACE:${THIRD_PARTY_DIR}/assimp/include>
    $<BUILD_INTERFACE:${THIRD_PARTY_DIR}/spdlog/include>
    $<BUILD_INTERFACE:${THIRD_PARTY_DIR}/imgui>
)

# FOLDER是一个比较有用的属性。在许多集成开发环境（IDE）中，当生成项目文件时，这个属性用于对目标进行分组。在这个例子中，将目标${TARGET_NAME}放在名为Engine的组中。
set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 20 OUTPUT_NAME "ExCCCEditor")
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "Engine")

# 检查编译器是否是MSVC, 如果是则增加编译选项 /WX
target_compile_options(${TARGET_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/WX->")

target_link_libraries(${TARGET_NAME} ExCCCRuntime)



