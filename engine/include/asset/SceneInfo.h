#pragma once
#include <cstdint>
#include <vector>
#include "core/math/vector/Vector.hpp"
#include "core/math/Point.h"
namespace ExCCCRender::Asset{
using namespace ExCCCRender::Core::Math;

struct Vertex{
    int32_t id;        // * 顶点编号
    Vector3D normal;   // * 顶点法线
    Vector3D tangent;  // * 切线信息
    Vector3D bitangent;// * 副切线信息
    Vector3D position; // * 顶点位置
    Vector2D tex_coord;// * 纹理坐标, 合理性存疑
};
struct Face{
    int32_t id;                      // * 面 id
    Vector3D normal;                 // * 面法线
    std::vector<int32_t> vertex_ids; // * 面对应的点的id, 不一定非要是三角形
};
/*
 * 保存一个Mesh的完整信息:
 * - 顶点信息
 * - 面索引信息
 * - 法线信息
 * - AABB 以及内部递归子结构
 * - 贴图信息
 */
struct MeshInfo{
    int32_t id{-1}; // * Mesh id
    // * 局部坐标系 min 和 max
    Point3D aabb_min;
    Point3D aabb_max;
    std::vector<Vertex> vertexs;
    std::vector<Face> faces;
    // * 纹理映射

    // * 材质信息

};

struct LightInfo{
    Vector3D position; // * 光源位置
    Vector3D color;    // * 光源颜色
    float intensity;   // * 光源强度
};

struct CameraInfo{};

struct Scene{
    std::vector<MeshInfo> meshes;
    std::vector<LightInfo> lights;
    std::vector<CameraInfo> carmers;
};



}