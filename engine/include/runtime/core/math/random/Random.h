#pragma once
#include <concepts>
#include <cstdint>
#include <ctime>
#include <concepts>
#include <random>
#include <limits>
#include <numeric>
#include "Distribution.h"
#include "runtime/core/traits.hpp"

namespace ExCCCRender::Core::Math {

struct RandomGenerator final {
public:
    static RandomGenerator& Instance() {
        static RandomGenerator generator;
        return generator;
    }

    template <Arithmetic RetType, RandomGen Gen = std::mt19937_64, typename Distribution>
    int64_t Generator(int64_t left, int64_t right, Gen generator) {
        std::mt19937                           rng(seed);
        std::uniform_int_distribution<int64_t> uni(left, right);
        return uni(rng);
    }

private:
    RandomGenerator()                                  = default;
    RandomGenerator(const RandomGenerator&)            = delete;
    RandomGenerator& operator=(const RandomGenerator&) = delete;

private:
    // * 从硬件电路中取一个随机数, 相当于真随机
    std::random_device seed;
};

}  // namespace ExCCCRender::Core::Math