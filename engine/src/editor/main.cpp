#include <cstdint>
#include <iostream>
#include <array>
#include "runtime/core/math/vector_detail.hpp"
#include "runtime/core/math/Vector.hpp"
#include <fmt/format.h>

using namespace ExCCCRender::Core::Math;
int main() {
    Vector3D v1 = Vector3D(1,2,3.14);
    std::cout << v1.X() << " " << v1.Y() << " " << v1.Z() << std::endl;
    Vector3D v2 = Vector3D(1,2,3.14);
    v1 += v2;
    std::cout << v1.X() << " " << v1.Y() << " " << v1.Z() << std::endl;
    return 0;
}