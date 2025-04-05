#include "asset/AssetLoader.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

namespace ExCCCRender::Asset {
MeshInfo& AssetLoader::load_one_file_(const std::string_view path) {
    Assimp::Importer importer;
    auto             path_ = path.data();

    const aiScene * scene = importer.ReadFile(
        path_,                               // * 资源路径
        aiProcess_Triangulate          |     // * 全部成三角面片
        aiProcess_GenNormals           |     // * 没有法线则生成法线
        aiProcess_CalcTangentSpace     |     // * 计算切线和副切线，用于法线贴图。
        aiProcess_JoinIdenticalVertices|     // * 合并重复顶点以减少数据量
        aiProcess_ImproveCacheLocality |     // * 优化顶点缓存命中率
        aiProcess_MakeLeftHanded       |     // * 左手系
        aiProcess_GenBoundingBoxes           // * 生成包围盒
    );
}
}  // namespace ExCCCRender::Asset