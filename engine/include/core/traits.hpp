#pragma once
#include <type_traits>
#include <concepts>

template <typename Ty>
concept Arithmetic = std::is_arithmetic<Ty>::value;


template <typename T, typename U>
concept DerivedFrom = std::is_base_of_v<U, T>;

