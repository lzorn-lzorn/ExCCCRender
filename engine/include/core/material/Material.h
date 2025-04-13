#pragma once
#include "core/illumination/Color.h"
#include "core/illumination/Ray.h"
// #include "core/scene/HitInfo.h"
#include "core/math/Point.h"
// 材质基类
namespace ExCCCRender::Core::Material{
using namespace ExCCCRender::Core::Illumination;
// ! 观察一下这里会不会报错, 找不到具体的HitInfo
// ! 因为这里注释了 HitInfo 所在的命名空间, 应该是找不到这个名字才对
// using namespace ExCCCRender::Core::Scene;

struct HitInfo;
struct Pdf;
struct ScatterRecord;
class Material{
public: 
// @function: 是否会散射函数
    virtual bool scatter(const Ray &r_in, const HitInfo &rec, RGB &attenuation, Ray &scattered) const {
        return false;
    }

    virtual bool scatter(const Ray &r_in, const HitInfo &rec, RGB &attenuation, Ray &scattered,
                         double &pdf) const {
        return false;
    }

    // virtual bool scatter(Ray &r_in, const HitInfo &rec, scatter_record &srec) const {
    //     return false;
    // }

    virtual double scattering_pdf(const Ray &r_in, const HitInfo &rec, const Ray &scattered) const {
        return 0.0;
    }
// @function: 自发光
    virtual RGB emitted(double u, double v, const Point3D &p) const {
        return RGB(0, 0, 0);
    }

    virtual RGB emitted(const Ray &r_in, const HitInfo &rec, double u, double v, const Point3D &p) const {
        return RGB(0, 0, 0);
    }
};
}