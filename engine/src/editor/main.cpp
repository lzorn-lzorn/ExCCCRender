#include <cstdint>
#include <iostream>
#include <array>
#include "runtime/core/math/random/Random.h"
#include <fmt/core.h>

using namespace ExCCCRender::Core::Math;
int main() {
    for(size_t i = 0; i < 10; ++i){
        std::cout << RandomGenerator::Instance().Generate<float>(0, 100) << " ";
    }
    std::cout << std::endl;
    return 0;
}