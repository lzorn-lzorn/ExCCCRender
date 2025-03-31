#include <cstdint>
#include <iostream>
#include <array>
#include "runtime/core/math/vector/vector_detail.hpp"
#include "runtime/core/math/vector/Vector.hpp"
#include <fmt/core.h>

using namespace ExCCCRender::Core::Math;
int main() {
    std::vector<int> vec{1,2,3,4};
    std::cout << sizeof(vec) << std::endl;
    return 0;
}