#pragma once
#include "asset/SceneInfo.h"
#include "core/math/Point.h"
#include "core/illumination/Ray.h"
#include "HitInfo.h"
#include <vector>
namespace ExCCCRender::Scene {
using namespace ExCCCRender::Asset;
using namespace ExCCCRender::Core::Math;
using namespace ExCCCRender::Core::Illumination;

// * AABB 内部再切分, 用于快速定位三角形
// * Eg: AABBDiviedNumber = 4, 则 AABB 内部划分为 4*4*4 = 64 个小立方体
constexpr size_t AABBDiviedNumber = 3;
struct AABBRange{
    AABBRange() = default;
    explicit AABBRange(const Point3D& min, const Point3D& max) : min(min), max(max) {}
    HitInfo& Hit() const;
    bool IsHit(const Ray& ray, double min_time, double max_time) const;

private:
    Point3D min; // * AABB的最小点
    Point3D max; // * AABB的最大点
    const MeshInfo* mesh; // * AABB包围的Mesh
};


/*
 * @note: AABB 是 Mesh 的包围盒子, 其包裹了一个完整的模型(Mesh网格)
 *        AABB内部使用基于空间均匀划分的八叉树来加速求交运算
 */
struct AABB{
public:
    /*
     * @function: 初始化AABB, 使用MeshInfo内部存储的max和min信息进行一个初始化
     *            初始化时, 使用八叉树划分空间, 加速查找求交
     * @note: MeshInfo 中 aabb_min 和 aabb_max 是局部坐标系, 这里的可能需要转换为世界坐标
     * @param1: AABB包围的 Mesh, @param2: 该Mesh的局部坐标的原点, 位于世界坐标的哪个点
     */
    explicit AABB() = default;
    explicit AABB(const Point3D& min, const Point3D& max)
        : min(min), max(max), hit_record(nullptr), mesh(nullptr) {
        areas.reserve(AABBDiviedNumber * AABBDiviedNumber * AABBDiviedNumber);

    }
    explicit AABB(const MeshInfo& m, const Point3D& p=Point3D{0,0,0}) : mesh(&m) {}
    AABB& operator=(AABB&&)      = default;
    ~AABB()                      = default;
    AABB(AABB&&)                 = default;

    AABB(const AABB&)            = delete;
    AABB& operator=(const AABB&) = delete;

public:
    // * 获取最外面包围盒的两个对角点
    Point3D Max() const;
    Point3D Min() const;
    // * 光线Ray是否击中最外层包围盒
    bool IsHit(const Ray& ray, double min_time, double max_time);
    // * 判断光线是否与某一个三角形有交点
    bool IsIntersect(const Ray& ray);
    // * 获取交点处信息
    HitInfo& GetHitInfo() const;
private:
    // * 划分最大的AABB为小的aabb, 并填充进 areas 数组中。
    // * 划分Mesh至更小的aabb中
    void _fill_areas();

private:
    HitInfo* hit_record;
    Point3D min; // * AABB的最小点
    Point3D max; // * AABB的最大点
    std::vector<AABBRange> areas; // * AABB内部划分的区域
    const MeshInfo* mesh;
};

AABB MergeBox(AABB box1, AABB box2);

}