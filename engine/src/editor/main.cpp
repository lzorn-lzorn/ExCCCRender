
#include <iostream>
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include <fmt/core.h>
int main() {
    std::cout << "Hello Assimp" << std::endl;
    std::cout.flush();
    // 创建 Importer 实例
    Assimp::Importer importer;

    // 加载 .blend 文件，并应用后处理（如三角化、生成法线）
    const aiScene* scene = importer.ReadFile(
        "G:/CppCode/ExCCCRender/asserts/GirlWithAPearlEarring.fbx",
        aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_FlipUVs
    );

    // 检查加载是否成功
    if (!scene || !scene->mRootNode) {
        std::cerr << "FAILED: " << importer.GetErrorString() << std::endl;
        return -1;
    }


    // 输出加载信息
    std::cout << "SUCCESS: " << scene->mNumMeshes << std::endl;
    system("pause");
    return 0;
}