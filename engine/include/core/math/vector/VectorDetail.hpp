#pragma once
#include <tuple>
#include <utility>
#include "pch.hpp"
#include "tools/parser/ConfigParser.hpp"
#include "tools/static_for.hpp"
#include "core/traits.hpp"

namespace ExCCCRender::Core::Math::detail {
using namespace ExCCCRender::Tools;

template <Arithmetic Ty, size_t N>
struct VectorBase {

    using value_type = Ty;
    constexpr static size_t Dimension = N;

    explicit VectorBase() {
    }

    explicit VectorBase(std::initializer_list<value_type> list) {
        coordinates = std::array<value_type, N>(list.begin(), list.end());
    }

    template <Arithmetic... Args>
    explicit VectorBase(const Args&... args) : coordinates{} {
        static_assert(sizeof...(Args) == N, "sizeof...(Args) != N, 参数数量与向量维度不符");
        construct_helper(std::make_index_sequence<N>{}, args...);
    }

    VectorBase(const VectorBase& other) {
        static_for<N>([&](size_t i) {
            coordinates[i] = other.coordinates[i];
        });
    }

    VectorBase(VectorBase&& other) {
        static_assert(N == VectorBase::Dimension, "vector 要同一维度");
        if (other == *this) {
            return;
        }
        coordinates.swap(other.coordinates);
    }

    VectorBase& operator=(const VectorBase& other) {
        auto vec = other;
        return vec;
    }

    VectorBase& operator=(VectorBase&& other) {
        static_assert(N == VectorBase::Dimension, "向量维度不一致");
        if (other == *this) {
            return *this;
        }
        *this->coordinates.swap(other.coordinates);
        return *this;
    }

    bool operator==(const VectorBase& other) const {
        static_assert(N == VectorBase::Dimension, "向量维度不一致");
        if (other.coordinates.size() != coordinates.size()) {
            return false;
        }
        bool ret = true;
        static_for<N>([&](size_t i) {
            ret &= coordinates[i] == other.coordinates[i];
        });
        return ret;
    }

    VectorBase& operator-() {
        static_for<N>([&](size_t i) {
            coordinates[i] = -coordinates[i];
        });
        return *this;
    }

    VectorBase& operator+=(const value_type number) {
        static_for<N>([&](size_t i) {
            coordinates[i] += number;
        });
        return *this;
    }

    VectorBase& operator+=(const VectorBase& vec) {
        static_assert(N == VectorBase::Dimension, "向量维度不一致");
        static_for<N>([&](size_t i) {
            coordinates[i] += vec.coordinates[i];
        });
        return *this;
    }

    VectorBase& operator-=(const VectorBase& vec) {
        static_assert(N == VectorBase::Dimension, "向量维度不一致");
        static_for<N>([&](size_t i) {
            coordinates[i] -= vec.coordinates[i];
        });
        return *this;
    }

    VectorBase& operator-=(const value_type number) {
        return operator+=(-number);
    }



    template <Arithmetic... Args>
    VectorBase& mutli_add(const Args&... args) {
        static_assert(sizeof...(Args) == N, "参数数量要和向量维度保持一致");
        [&]<std::size_t... Index>(std::index_sequence<Index...>) {
            ((coordinates[Index] += std::get<Index>(std::forward_as_tuple(args...))), ...);
        }(std::make_index_sequence<N>());
        return *this;
    }

    VectorBase& hadamard_product(const VectorBase other) {
        static_assert(other.coordinates.size() == N, "两个向量维度保持一致");
        static_for<N>([&](auto i) {
            coordinates[i] *= other.coordinates[i];
        });
        return *this;
    }

    bool is_zero_vector() const noexcept {
        bool ret     = true;
        auto epsilon = std::numeric_limits<value_type>::epsilon();
        static_for<0, N>([&](size_t i) {
            if (coordinates[i] <= epsilon) {
                ret = false;
            }
        });
        return ret;
    }

    bool is_unit_vector() const noexcept {
        return square_sum() == 1;
    }

    bool is_axis() const noexcept {
        size_t count = 0;
        static_for<N>([&](size_t i) {
            if (coordinates[i] == 1) {
                ++count;
            } else if (coordinates[i] != 0) {
                count = 2;  // 直接标记为不符合条件
            }
        });
        return count == 1;
    }

    VectorBase& normalize() {
        if (is_unit_vector()) {
            return *this;
        }
        auto square_ = square_sum();
        if (square_ == 1) {
            return *this;
        }
        auto size_ = std::sqrt(square_);
        static_for<N>([&](size_t i) {
            coordinates[i] /= size_;
        });
        return *this;
    }

    double dot(const VectorBase& vec) const {
        static_assert(VectorBase::Dimension == N, "Vector维度不一致");
        double res{};
        static_for<N>([&](size_t i) {
            res += coordinates[i] * vec.coordinates[i];
        });
        return res;
    }

    double dot(const VectorBase& vec) {
        static_assert(VectorBase::Dimension == N, "Vector维度不一致");
        double res{};
        static_for<N>([&](size_t i) {
            res += coordinates[i] * vec.coordinates[i];
        });
        return res;
    }

    VectorBase& proportionally_change(const value_type ratio) {
        static_for<N>([&](size_t i) {
            coordinates[i] *= ratio;
        });
        return *this;
    }

    double length() const noexcept {
        if (is_unit_vector()) {
            return 1.0;
        }
        return std::sqrt(square_sum());
    }

    // * 返回 x*x+y*y+z*z
    double square_sum() const noexcept {
        double res = 0;
        static_for<N>([&](size_t i) {
            res += coordinates[i] * coordinates[i];
        });
        return res;
    }

    std::array<value_type, N> coordinates;

private:
    template <Arithmetic... Args, size_t... Index>
    void construct_helper(std::index_sequence<Index...>, const Args&... args) {
        ((coordinates[Index] = args), ...);
    }

    template <Arithmetic... Args, size_t... Index>
    void add_helper(const Args&... args, std::index_sequence<Index...>) {
        ((coordinates[Index] += args), ...);
    }
};

template <Arithmetic value_type, size_t N>
inline VectorBase<value_type, N> Normalize(const VectorBase<value_type, N>& vec) {
    VectorBase<value_type, N> ret(vec);
    if (vec.is_unit_vector()) {
        return ret;
    }
    ret.Normalize();
    return ret;
}

template <Arithmetic value_type, size_t N>
inline VectorBase<value_type, N> Zoom(const VectorBase<value_type, N>& vec, const value_type ratio) {
    VectorBase<value_type, N> ret(vec);
    ret.Zoom(ratio);
    return ret;
}

template <Arithmetic value_type, size_t N>
inline VectorBase<value_type, N> HadamardProduct(const VectorBase<value_type, N>& vec1, const VectorBase<value_type, N>& vec2) {
    VectorBase<value_type, N> ret(vec1);
    ret.HadamardProduct(vec2);
    return ret;
}

template <Arithmetic value_type, size_t N>
inline VectorBase<value_type, N> Dot(const VectorBase<value_type, N>& vec1, const VectorBase<value_type, N>& vec2) {
    return VectorBase<value_type, N>(vec1.dot(vec2));
}

}  // namespace ExCCCRender::Core::Math::detail

using namespace ExCCCRender::Core::Math::detail;
template <typename T>
concept VectorType = requires {
    typename T::value_type;
    requires requires (T t) {
        []<typename Ty, size_t N>(const VectorBase<Ty, N>&){}(t);
    };
};