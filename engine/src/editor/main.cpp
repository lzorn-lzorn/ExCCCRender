#include <cstdint>
#include <iostream>
#include <array>
#include "runtime/core/math/vector_detail.hpp"


#include <array>
#include <utility> // for std::index_sequence

template<typename T, std::size_t N>
class Vector {
public:
    // 使用折叠表达式直接展开参数包
    template<typename... Args>
    void multi_add(const Args&... args) {
        static_assert(sizeof...(Args) == N, "参数数量必须和向量维度一致");

        // 使用立即调用 lambda 和 std::index_sequence 展开参数包
        [&]<std::size_t... I>(std::index_sequence<I...>) {
            ((p_coordinates[I] += std::get<I>(std::forward_as_tuple(args...))), ...);
        }(std::make_index_sequence<N>{});
    }
    std::array<T, N> p_coordinates;
};

int main() {
    Vector<double, 3> vec; // 3维向量
    vec.multi_add(1.0, 2.0, 3.0); // p_coordinates[0]+=1.0, [1]+=2.0, [2]+=3.0
    std::cout << vec.p_coordinates[0] << std::endl;
    std::cout << vec.p_coordinates[1] << std::endl;
    std::cout << vec.p_coordinates[2] << std::endl;
    return 0;
}