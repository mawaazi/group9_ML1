#ifndef COEFFICIENT_OF_DETERMINATION_H
#define COEFFICIENT_OF_DETERMINATION_H

#include <vector>
#include <cmath>
#include <cstddef>
#include <type_traits>
#include <string>
#include "ml_error.hpp"

namespace ml1 {

template <typename T>
double coefficient_of_determination(
    const std::vector<T>& actual,
    const std::vector<T>& predicted)
{
    // 1. Compile-time validation
    static_assert(std::is_floating_point_v<T>, 
        "MLError: R² requires floating-point data (float, double, long double).");

    // 2. Runtime validation
    if (actual.empty() || predicted.empty()) {
        throw InvalidInputError("input vectors must not be empty");
    }
    if (actual.size() != predicted.size()) {
        throw InvalidInputError("actual and predicted must be the same size");
    }

    const std::size_t n = actual.size();
    for (std::size_t i = 0; i < n; ++i) {
        if (!std::isfinite(actual[i]) || !std::isfinite(predicted[i])) {
            throw InvalidInputError("input contains NaN or infinite value");
        }
    }

    // 3. Single-pass optimized calculation
    // We calculate sums to derive mean, SS_tot, and SS_res in ONE loop.
    long double sum_actual = 0.0L;
    long double sum_predicted = 0.0L;
    long double sum_actual_sq = 0.0L;
    long double sum_predicted_sq = 0.0L;
    long double sum_actual_predicted = 0.0L;

    for (std::size_t i = 0; i < n; ++i) {
        const long double a = static_cast<long double>(actual[i]);
        const long double p = static_cast<long double>(predicted[i]);

        sum_actual += a;
        sum_predicted += p;
        sum_actual_sq += a * a;
        sum_predicted_sq += p * p;
        sum_actual_predicted += a * p;
    }

    // 4. Algebraic derivation of SS_res and SS_tot
    const long double n_ld = static_cast<long double>(n);
    
    // SS_tot = sum(y^2) - (sum(y)^2 / n)
    const long double ss_tot = sum_actual_sq - (sum_actual * sum_actual / n_ld);
    
    // SS_res = sum((y - y_hat)^2) 
    //        = sum(y^2) - 2*sum(y*y_hat) + sum(y_hat^2)
    const long double ss_res = sum_actual_sq 
                             - 2.0L * sum_actual_predicted 
                             + sum_predicted_sq;

    if (ss_tot <= 0.0L) {
        throw InvalidInputError("all actual values are identical (SS_tot = 0); R² is undefined");
    }

    return static_cast<double>(1.0L - (ss_res / ss_tot));
}

} // namespace ml1

#endif // COEFFICIENT_OF_DETERMINATION_H