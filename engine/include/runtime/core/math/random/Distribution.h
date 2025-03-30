#pragma once
#include <concepts>
#include <type_traits>
#include <random>
#include "runtime/core/traits.hpp"

namespace ExCCCRender::Core::Math {
template <typename G>
concept RandomGen = std::uniform_random_bit_generator<G>;

template <std::signed_integral Ty>
using Bernoulli = std::bernoulli_distribution;

template <std::signed_integral Ty>
using Binomial = std::binomial_distribution<Ty>;

template <std::signed_integral Ty>
using Geometric = std::geometric_distribution<Ty>;

template <std::signed_integral Ty>
using NegativeBinomial = std::negative_binomial_distribution<Ty>;

template <std::signed_integral Ty>
using Poisson = std::poisson_distribution<Ty>;

template <std::signed_integral Ty>
using Discrete = std::discrete_distribution<Ty>;

template <Arithmetic Ty>
using Uniform =
    std::conditional<std::signed_integral<Ty>, std::uniform_int_distribution<Ty>, std::uniform_real_distribution<Ty>>;

template <Arithmetic Ty>
using Exponential = std::exponential_distribution<Ty>;

template <Arithmetic Ty>
using Gamma = std::gamma_distribution<Ty>;

template <Arithmetic Ty>
using Weibull = std::weibull_distribution<Ty>;

template <Arithmetic Ty>
using ExtremeValue = std::extreme_value_distribution<Ty>;

template <Arithmetic Ty>
using Normal = std::normal_distribution<Ty>;

template <Arithmetic Ty>
using Gaussian = std::normal_distribution<Ty>;

template <Arithmetic Ty>
using Lognormal = std::lognormal_distribution<Ty>;

template <Arithmetic Ty>
using ChiSquared = std::chi_squared_distribution<Ty>;

template <Arithmetic Ty>
using Cauchy = std::cauchy_distribution<Ty>;

template <Arithmetic Ty>
using Fisher = std::fisher_f_distribution<Ty>;

template <Arithmetic Ty>
using F = std::fisher_f_distribution<Ty>;

template <Arithmetic Ty>
using Student = std::student_t_distribution<Ty>;

template <Arithmetic Ty>
using T = std::student_t_distribution<Ty>;

template <Arithmetic Ty>
using Cauchy = std::cauchy_distribution<Ty>;

template <Arithmetic Ty>
using PiecewiseConstant = std::piecewise_constant_distribution<Ty>;

template <Arithmetic Ty>
using PiecewiseLinear = std::piecewise_linear_distribution<Ty>;

}  // namespace ExCCCRender::Core::Math
