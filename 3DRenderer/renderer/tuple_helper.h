#pragma once

#include <cstddef>
#include <tuple>

#include "renderer/types.h"

/**
 * @brief Calls fn(get<I>(t0), get<I>(ts)...) for every index I in t0,
 * walking all tuples in lockstep. Used to apply a per-field operation
 * across multiple instances of the same Varying type simultaneously.
 */
template <size_t I = 0, typename Fn, typename Tuple, typename... Tuples>
void tuple_iterate(Fn&& fn, Tuple&& t0, Tuples&&... ts) {
    if constexpr (I < std::tuple_size_v<std::decay_t<Tuple>>) {
        fn(std::get<I>(t0), std::get<I>(ts)...);
        tuple_iterate<I + 1>(std::forward<Fn>(fn), std::forward<Tuple>(t0),
                          std::forward<Tuples>(ts)...);
    }
}

/**
 * @brief Barycentric-blends all VARYING fields of a user-defined Varying type
 * using weights wA, wB, wC. All fields must be float Eigen vectors.
 */
template <typename TVarying>
TVarying interpolate_fragment_data(const TVarying& v0, const TVarying& v1,
                                   const TVarying& v2, float wA, float wB,
                                   float wC) {
    static_assert(has_reflect<TVarying>::value,
                  "TVarying must define VARYING(...) macro");
    TVarying result;
    tuple_iterate(
        [&](auto& res, const auto& x0, const auto& x1, const auto& x2) {
            res = wA * x0 + wB * x1 + wC * x2;
        },
        result._reflect(), v0._reflect(), v1._reflect(), v2._reflect());
    return result;
}
