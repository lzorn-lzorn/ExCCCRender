#pragma once
#include <utility>
#include "pch.hpp"
#include "runtime/core/traits.hpp"
namespace ExCCCRender::Core::Math::detail {
        template <size_t N>
        struct vector_n{
        public:
            explicit vector_n(std::initializer_list<float> list){
                p_coordinates = std::array<float, N>(list.begin(), list.end());
            }
            template <Arithmetic... Args>
            explicit vector_n(const Args&... args) : p_coordinates{}{
                static_assert(sizeof...(Args) == N, "sizeof...(Args) != N, 参数数量与向量维度不符");
                construct_helper(std::make_index_sequence<N>{}, args...);
            }
            vector_n(const vector_n& other){
                static_for([&](size_t i){
                    p_coordinates[i] = other.p_coordinates[i];
                });
            }
            vector_n(vector_n&& other){
                static_assert(p_coordinates.size() == other.p_coordinates.size(), "vector 要同一维度");
                if (other == *this){
                    return;
                }
                p_coordinates.swap(other.p_coordinates);
            }
            vector_n& operator=(const vector_n& other){
                auto vec = other;
                return vec;
            }
            vector_n& operator=(vector_n&& other){}
            bool operator==(const vector_n& other){
                static_assert(other.p_coordinates.size() == p_coordinates.size(), "向量维度不一致");
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
                auto epsilon = std::numeric_limits<float>::epsilon();
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
            double dot(const vector_n& vec) const {
                static_assert(vec.p_coordinates.size()==p_coordinates.size(), "Vector维度不一致");
                double res{};
                static_for<N>([&](size_t i){
                    res += p_coordinates[i] * vec.p_coordinates[i];
                });
                return res;
            }
            double dot(const vector_n& vec) {
                static_assert(vec.p_coordinates.size()==p_coordinates.size(), "Vector维度不一致");
                double res{};
                static_for<N>([&](size_t i){
                    res += p_coordinates[i] * vec.p_coordinates[i];
                });
                return res;
            }
            void proportionally_change(const float ratio){
                static_for<N>([&](size_t i){
                    p_coordinates[i] *= ratio;
                });
            }
            double length() const noexcept{
                if (is_unit_vector()){
                    return 1.0;
                }
                return std::sqrt(square_sum());
            }

            // * 返回 x*x+y*y+z*z
            double square_sum() const noexcept{
                double res = 0;
                static_for<N>([&](size_t i){
                    res += p_coordinates[i] * p_coordinates[i];
                });
                return res;
            }
        public:
            std::array<float, N> p_coordinates;
        private:
            template <Arithmetic... Args, size_t... Index>
            void construct_helper(std::index_sequence<Index...>, const Args&... args){
                static_assert(sizeof...(Args) == N, "参数数量必须与数组长度一致");
                ((p_coordinates[Index] = args), ...);
            }
        };
    }