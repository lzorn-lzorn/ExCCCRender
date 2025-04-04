
#include "runtime/core/math/utility/Utility.h"
#include "runtime/core/math/vector/Vector.hpp"
#include <limits>

namespace ExCCCRender::Core::Math {

bool IsIntersectWithTriangle(const Ray& ray, const Point3D& p1, const Point3D& p2, const Point3D& p3) {
    auto edge1       = p2 - p1;
    auto edge2       = p3 - p1;
    auto h           = Cross(ray.direction, edge2);
    auto denominator = Dot(h, edge1);
    if (std::abs(denominator) < std::numeric_limits<float>::epsilon()) {
        std::cerr << "IsIntersectWithTriangle Error: denominator is zero\n";
        return false;
    }
    auto _tmp_denominator = 1.0f / denominator;
    auto origin_sub_p1    = ray.origin - p1;
    auto q                = Cross(origin_sub_p1, edge1);
    auto beta             = Dot(h, origin_sub_p1) * _tmp_denominator;
    if (beta < 0) {
        return false;
    }

    auto t = Dot(q, edge2) * _tmp_denominator;
    if (t < 0) {
        return false;
    }

    auto gamma = Dot(q, ray.direction) * _tmp_denominator;
    return gamma >= 0;
}
}  // namespace ExCCCRender::Core::Math
