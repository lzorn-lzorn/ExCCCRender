#include <cstdint>
#include <iostream>
#include <array>
#include "runtime/core/math/random/Random.h"
#include "runtime/core/illumination/Ray.h"
#include <fmt/core.h>

using namespace ExCCCRender::Core::Math;
using namespace ExCCCRender::Core::Illumination;
int main() {
    for(size_t i = 0; i < 10; ++i){
        std::cout << RandomGenerator::Instance().Generate<float>(0, 100, 10) << " ";
    }
    std::cout << std::endl;


    Ray ray(Point(0, 0, 0), Direction(1, 0, 0), 1);

    auto point = ray.At(0.5);

    return 0;
}