#pragma once
#include <concepts>
#include <span>
#include <cstdint>
#include <ctime>
#include <concepts>
#include <random>
#include <limits>
#include <numeric>
#include <utility>
#include "Distribution.h"
#include "runtime/core/traits.hpp"

namespace ExCCCRender::Core::Math {
/*
 * 随机数生成器:
 * 随机数生成器封装了C++标准库的 random, 旨在可以更方便更有可读性的生成随机数
 *
 */
struct RandomGenerator final {
public:
    static RandomGenerator& Instance() {
        static RandomGenerator generator;
        generator.seed = std::random_device{}();
        return generator;
    }

    /*
     * @function：生成一个随机数
     * @param: 区间 [left, right] 默认 [0,1]
     * @param: 随机数种子, 默认去硬件电路中取一个随机数作为种子
     * @param: 随机数服从的分布, 默认是高斯分布, Distribution.h 中封装了所有标准库支持的分布
     * @param: 随机数生成器, 默认使用 std::default_random_engine, 可以使用标准库的其他随机数生成器,
     *         同时可以自己封装随机数生成器, 见 RandomGenerator.h
     * @return：生成的随机数, 其类型为 RetType (可计算类型)
     */
    template <Arithmetic RetType,
              typename SeedType     = std::random_device,
              typename Distribution = Gaussian<RetType>,
              RandomGen Gen         = std::default_random_engine>
    RetType Generate(int64_t  left      = 0,
                     int64_t  right     = 1,
                     uint32_t seed      = std::random_device{}(),
                     Gen      generator = Gen{}) {
        this->seed = seed;
        generator(this->seed);
        Distribution dist(left, right);
        return dist(generator);
    }

    /*
     * @function：生成一个随机数序列
     * @param: 返回序列的大小
     * @param: 区间 [left, right] 默认 [0,1]
     * @param: 随机数种子, 默认去硬件电路中取一个随机数作为种子
     * @param: 随机数服从的分布, 默认是高斯分布, Distribution.h 中封装了所有标准库支持的分布
     * @param: 随机数生成器, 默认使用 std::default_random_engine, 可以使用标准库的其他随机数生成器,
     *         同时可以自己封装随机数生成器, 见 RandomGenerator.h
     * @return：生成的随机数, 其类型为 RetType (可计算类型)
     */
    template <Arithmetic RetType,
              typename SeedType     = std::random_device,
              typename Distribution = Gaussian<RetType>,
              RandomGen Gen         = std::default_random_engine>
    std::span<RetType> Generate(uint32_t number,
                                int64_t  left      = 0,
                                int64_t  right     = 1,
                                uint32_t seed      = std::random_device{}(),
                                Gen      generator = Gen{}) {
    }

public:
    uint32_t seed;

private:
    RandomGenerator()                                  = default;
    RandomGenerator(const RandomGenerator&)            = delete;
    RandomGenerator& operator=(const RandomGenerator&) = delete;
};

}  // namespace ExCCCRender::Core::Math