#pragma once
#include <type_traits>

template <typename Ty>
concept Arithmetic = std::is_arithmetic<Ty>::value;