#pragma once
#include "runtime/core/illumination/Point.h"
#include "runtime/core/math/vector/VectorOperator.h"

namespace ExCCCRender::Core::Illumination {
using namespace ExCCCRender::Core::Math;

struct Ray{
public:
    explicit Ray() = default;
    explicit Ray(const Point& origin, const Direction& direction, const double time = 0.0) : origin(origin), direction(direction), time(time) {

    }

    Point At(const float time) {
        return origin + time * direction;
    }
public:
    Point origin;
    Direction direction;
    double time;
};
}

