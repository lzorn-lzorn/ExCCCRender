set(third_party_folder "ThirdParty") # 设置项目生成后的文件夹名称 "ThirdParty"

# if(NOT TARGET imgui)
# include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/imgui.cmake)
# set_target_properties(imgui PROPERTIES FOLDER ${third_party_folder}/imgui) # 生成之后imgui在"ThirdParty/imgui"中
# endif()
if(NOT TARGET glfw)
    option(GLFW_BUILD_EXAMPLES "" OFF)
    option(GLFW_BUILD_TESTS "" OFF)
    option(GLFW_BUILD_DOCS "" OFF)
    option(GLFW_INSTALL "" OFF)
    add_subdirectory(glfw3)
    set_target_properties(glfw PROPERTIES FOLDER ${third_party_folder}/glfw)
    set_target_properties(update_mappings PROPERTIES FOLDER ${third_party_folder}/glfw)
endif()

include(find_stb.cmake)
include(find_spdlog.cmake)

# if(NOT TARGET assimp)
# add_subdirectory(assimp)
# set_target_properties(assimp PROPERTIES FOLDER ${third_party_folder}/assimp)
# set_target_properties(uninstall PROPERTIES FOLDER ${third_party_folder}/assimp)
# endif()
