#pragma once

namespace ExCCCRender::Core::Math {
struct XORShift32 {
    using result_type = uint32_t;

    // ! seed 不能为 0
    explicit XORShift32(result_type seed) : seed(static_cast<result_type>(seed + 1)) {
    }

    constexpr result_type operator()() noexcept {
        result_type x = seed;
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        return seed = x;
    }

    static constexpr result_type min() noexcept {
        return 1;
    }

    static constexpr result_type max() noexcept {
        return std::numeric_limits<result_type>::max();
    }

private:
    result_type seed = 1;
};

struct ThomasWangHash {
    using result_type = uint32_t;

    // ! seed 不能为 0
    explicit ThomasWangHash(result_type seed) : seed(static_cast<result_type>(seed + 1)) {
    }

    constexpr result_type operator()() noexcept {
        result_type x = seed;

        x = (x ^ 61) ^ (x >> 16);
        x *= 9;
        x = x ^ (x >> 4);
        x *= 0x27d4e2d;
        x = x ^ (x >> 15);

        return seed = x;
    }

    static constexpr result_type min() noexcept {
        return 0;
    }

    static constexpr result_type max() noexcept {
        return std::numeric_limits<result_type>::max();
    }

private:
    result_type seed = 1;
};
}  // namespace ExCCCRender::Core::Math