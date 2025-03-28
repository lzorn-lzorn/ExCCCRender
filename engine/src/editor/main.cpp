#include <cstdint>
#include <iostream>
#include <array>
#include "runtime/core/math/vector_detail.hpp"

int main() {
    using namespace ExCCCRender::Core::Math::detail;
    vector_n<3> vec_3(1,2,3);
    std::cout << vec_3.p_coordinates[0] << " " << vec_3.p_coordinates[1] << " " << vec_3.p_coordinates[2] << std::endl;
    return 0;
}
