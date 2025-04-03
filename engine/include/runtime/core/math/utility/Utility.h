#pragma once
#include "runtime/core/math/Point.h"
#include "runtime/core/illumination/Ray.h"
namespace ExCCCRender::Core::Math{
using namespace ExCCCRender::Core::Illumination;

// * @function: 直线与空间三角形的求交算法: Möller–Trumbore算法
// * @param ray: 直线
// * @param p1, p2, p3: 三角形的三个顶点
/*
 * 解以下方程组
 * [-direction, p2-p1, p3-p1] [t, \beta, \gamma]^T = [origin-p0]
 * @return: t>=0 && \beta>=0 && \gamma>=0 && \beta+\gamma<=1 
 */
bool IsIntersectWithTriangle(const Ray& ray, const Point3D& p1, const Point3D& p2, const Point3D& p3);
}