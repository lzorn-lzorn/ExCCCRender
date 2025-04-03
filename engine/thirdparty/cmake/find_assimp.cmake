
if(WIN32)
# Windows 下的文件
    set(ASSIMP_IMPORT_SHARED_LIB ${ExCCCRender_THIRDPARTY_DIR}/assimp/bin/assimp-vc143-mtd.dll)
    set(ASSIMP_IMPORT_STATIC_LIB ${ExCCCRender_THIRDPARTY_DIR}/assimp/lib/assimp-vc143-mtd.lib)
else()
# Linux 下的路径待补充
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${ExCCCRender_THIRDPARTY_DIR}/assimp/include)

add_library(assimp SHARED IMPORTED)
set_target_properties(assimp PROPERTIES
    IMPORTED_LOCATION ${ASSIMP_IMPORT_SHARED_LIB}
    IMPORTED_IMPLIB ${ASSIMP_IMPORT_STATIC_LIB}
)
target_link_libraries(${PROJECT_NAME} PUBLIC assimp)