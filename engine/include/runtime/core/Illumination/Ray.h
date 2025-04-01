#pragma once
#include "runtime/core/illumination/Point.h"

namespace ExCCCRender::Core::Illumination {
using namespace ExCCCRender::Core::Math;

struct Ray{
public:
    explicit Ray() = default;
    explicit Ray(const Point& origin, const Direction& direction, const double time = 0.0)
    : origin(origin), direction(Normalize<Direction>(direction)), time(time) {
        // 直接在初始化列表中归一化，不要修改参数
    }

    Point At(const float time) {
        return origin + time * direction;
    }
public:
    Point origin;
    Direction direction;
    double time;
};

inline Direction Reflect(const Ray& ray, const Vector3D& normal) {
    return ray.direction - 2 * ray.direction.Dot(normal) * normal;
}
inline Direction Reflect(const Direction& direction, const Vector3D& normal) {
    return direction - 2 * direction.Dot(normal) * normal;
}
}
