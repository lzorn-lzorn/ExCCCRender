
add_subdirectory(${ExCCCRender_THIRDPARTY_DIR}/fmt)
# ${PROJECT_NAME} == thirdparty
target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt)
target_include_directories(thirdparty PUBLIC ${ExCCCRender_THIRDPARTY_DIR})