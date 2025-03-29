add_subdirectory(${ExCCCRender_THIRDPARTY_DIR}/fmt)
target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt)
target_include_directories(${PROJECT_NAME} PUBLIC ${ExCCCRender_THIRDPARTY_DIR}/fmt/include)