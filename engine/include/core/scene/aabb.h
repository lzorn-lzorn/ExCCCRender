#pragma once
#include "asset/MeshInfo.h"
#include "core/math/Point.h"
#include "core/illumination/Ray.h"
#include "HitInfo.h"
namespace ExCCCRender::Scene {
using namespace ExCCCRender::Asset;
using namespace ExCCCRender::Core::Math;
using namespace ExCCCRender::Core::Illumination;
/*
 * @note: AABB 是 Mesh 的包围盒子, 其包裹了一个完整的模型(Mesh网格)
 *        AABB内部使用基于空间均匀划分的八叉树来加速求交运算
 *
 */
struct AABB{
public:
    /*
     * @function: 初始化AABB, 使用MeshInfo内部存储的max和min信息进行一个初始化
     *            初始化时, 使用八叉树划分空间, 加速查找求交
     * @note: MeshInfo 中 aabb_min 和 aabb_max 是局部坐标系, 这里的可能需要转换为世界坐标
     * @param1: AABB包围的 Mesh, @param2: 该Mesh的局部坐标的原点, 位于世界坐标的哪个点
     */
    explicit AABB(const MeshInfo& m, const Point3D& p=Point3D{0,0,0}) : mesh(&m) {}
    AABB(const AABB&)            = delete;
    AABB(AABB&&)                 = delete;
    AABB& operator=(const AABB&) = delete;
    AABB& operator=(AABB&&)      = delete;
    ~AABB()                      = default;
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
    HitInfo* hit_record;
    const MeshInfo* mesh;
};

struct AABBRange{
    explicit AABBRange(const Point3D& min, const Point3D& max) : min(min), max(max) {}
    HitInfo& Hit() const;
    bool IsHit(const Ray& ray, double min_time, double max_time) const;
private:
    bool _CheckHit() const;
private:
    Point3D min; // * AABB的最小点
    Point3D max; // * AABB的最大点
    const MeshInfo* mesh; // * AABB包围的Mesh
};
}