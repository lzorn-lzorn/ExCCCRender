#pragma once
#include "runtime/core/math/vector/Vector.hpp"
#include "runtime/core/illumination/Ray.h"

namespace ExCCCRender::Core::Math {
using namespace ExCCCRender::Core::Illumination;
/*
 * @function: 判断光线ray是否与空间三角形相交
 * @param: ray 光线
 * @param: p1,p2,p3: 三角形的三个顶点
 */
bool IsIntersectWithTriangle(const Ray& ray, const Point3D& p1, const Point3D& p2, const Point3D& p3);
}  // namespace ExCCCRender::Core::Math