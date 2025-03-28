#pragma once
#include <utility>
#include "pch.hpp"
#include "runtime/core/traits.hpp"
namespace ExCCCRender::Tools::Math::detail {
        template <Arithmetic Ty, size_t N>
        struct vector_n{
            using value_type = Ty;
            // * 防止溢出类型
            using ResultType = std::conditional_t<std::is_integral_v<Ty>,
                    std::conditional_t<(sizeof(Ty) <= sizeof(int16_t)),
                        int16_t,
                        std::conditional_t<(sizeof(Ty) == sizeof(int32_t)),
                            int32_t,
                            std::conditional_t<(sizeof(Ty) == sizeof(int64_t)),
                                int64_t,
                                int64_t // int64 为最高
                            >
                        >
                    >,
                    std::conditional_t<std::is_floating_point_v<Ty>,
                        long double,
                        Ty
                    >
                >;
        public:
            explicit vector_n(std::initializer_list<Ty> list){
                p_coordinates = std::array<Ty, N>(list.begin(), list.end());
            }
            template <Arithmetic... Args, size_t... Index>
            explicit vector_n(const Args&... args) : p_coordinates{}{
                construct_helper(args..., std::make_index_sequence<N>{});
            }
            vector_n(const vector_n& other){

            }
            vector_n(vector_n&& other){
                static_assert(p_coordinates.size() == other.p_coordinates.size(), "vector 要同一维度");
                if (other == *this){
                    return;
                }
                p_coordinates.swap(other.p_coordinates);
            }
            vector_n& operator=(const vector_n& other){}
            vector_n& operator=(vector_n&& other){}
            bool operator==(const vector_n& other){
                if (other.p_coordinates.size() != p_coordinates.size()){
                    return false;
                }
                bool ret = true;
                static_for<N>([&](size_t i){
                    ret &= p_coordinates[i] == other.p_coordinates[i];
                });
                return  ret;
            }
        public:
            bool is_zero_vector() const noexcept{
                bool ret = true;
                auto epsilon = std::numeric_limits<Ty>::epsilon();
                static_for<0, N>([&](size_t i){
                    if constexpr (p_coordinates[i] <= epsilon){
                        ret = false;
                    }
                });
                return ret;
            }
            bool is_unit_vector() const noexcept{
                return square_sum() == 1;
            }
            bool is_axis() const noexcept{
                size_t count = 0;
                static_for<N>([&](auto i) {
                    if constexpr(p_coordinates[i] == 1) {
                        ++count;
                    } else if (p_coordinates[i] != 0) {
                        count = 2; // 直接标记为不符合条件
                    }
                });
                return count == 1;
            }
        public:
            void normalize() {
                if (is_unit_vector()){
                    return *this;
                }
                auto square_ = square_sum();
                if(square_ == 1){
                    return *this;
                }
                auto size_ = std::sqrt(square_);
                static_for<N>([&](size_t i){
                    p_coordinates[i] /= size_;
                });
            }
            auto dot(const vector_n& vec){
                ResultType res{};
                static_for<N>([&](size_t i){
                    res += p_coordinates[i] * vec.p_coordinates[i];
                });
            }
            double length() const noexcept{
                if (is_unit_vector()){
                    return 1.0;
                }
                return std::sqrt(square_sum());
            }

            // * 返回 x*x+y*y+z*z
            auto square_sum() const noexcept{
                ResultType res = 0;
                static_for<N>([&](size_t i){
                    res += p_coordinates[i] * p_coordinates[i];
                });
                return res;
            }
        public:
            std::array<Ty, N> p_coordinates;
        private:
            template <Arithmetic... Args, size_t... Index>
            void construct_helper(const Args&... args, std::index_sequence<Index...>){
                static_assert(sizeof...(Args) == N, "参数数量必须与数组长度一致");
                ((p_coordinates[Index] = args), ...);
            }
        };
    }